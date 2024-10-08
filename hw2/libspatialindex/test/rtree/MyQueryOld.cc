/******************************************************************************
 * Project:  libspatialindex - A C++ library for spatial indexing
 * Author:   Marios Hadjieleftheriou, mhadji@gmail.com
 ******************************************************************************
 * Copyright (c) 2002, Marios Hadjieleftheriou
 *
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
******************************************************************************/

// NOTE: Please read README.txt before browsing this code.

// include library header file.
#include <spatialindex/SpatialIndex.h>

using namespace SpatialIndex;

#define INSERT 1
#define DELETE 0
#define QUERY 2
using namespace std;
int dim=2;
class MyDataStream : public IDataStream
{
public:
	MyDataStream(std::string inputFile, ) : m_pNext(nullptr)
	{
		m_fin.open(inputFile.c_str());

		if (! m_fin)
			throw Tools::IllegalArgumentException("Input file not found.");

		readNextEntry();
	}

	~MyDataStream() override
	{
		if (m_pNext != nullptr) delete m_pNext;
	}

	IData* getNext() override
	{
		if (m_pNext == nullptr) return nullptr;

		RTree::Data* ret = m_pNext;
		m_pNext = nullptr;
		readNextEntry();
		return ret;
	}

	bool hasNext() override
	{
		return (m_pNext != nullptr);
	}

	uint32_t size() override
	{
		throw Tools::NotSupportedException("Operation not supported.");
	}

	void rewind() override
	{
		if (m_pNext != nullptr)
		{
			delete m_pNext;
			m_pNext = nullptr;
		}

		m_fin.seekg(0, std::ios::beg);
		readNextEntry();
	}

	void readNextEntry()
	{
		id_type id;
		uint32_t op;
		double low[dim], high[dim];

		m_fin >> op >> id //>> low[0] >> low[1] >> high[0] >> high[1];
		if (m_fin.good())
		{
			if (op != INSERT)
				throw Tools::IllegalArgumentException(
					"The data input should contain insertions only."
				);

			Region r(low, high, 2);
			m_pNext = new RTree::Data(sizeof(double), reinterpret_cast<uint8_t*>(low), r, id);
				// Associate a bogus data array with every entry for testing purposes.
				// Once the data array is given to RTRee:Data a local copy will be created.
				// Hence, the input data array can be deleted after this operation if not
				// needed anymore.
		}
	}

	std::ifstream m_fin;
	RTree::Data* m_pNext;
};

class MyVisitor : public IVisitor
{
public:
	size_t m_indexIO{0};
	size_t m_leafIO{0};

public:
    MyVisitor() = default;

	void visitNode(const INode& n) override
	{
		if (n.isLeaf()) m_leafIO++;
		else m_indexIO++;
	}

	void visitData(const IData& d) override
	{
		IShape* pS;
		d.getShape(&pS);
			// do something.
		delete pS;

		// data should be an array of characters representing a Region as a string.
		uint8_t* pData = nullptr;
		uint32_t cLen = 0;
		d.getData(cLen, &pData);
		// do something.
		//string s = reinterpret_cast<char*>(pData);
		//cout << s << endl;
		delete[] pData;

		cout << d.getIdentifier() << endl;
			// the ID of this data entry is an answer to the query. I will just print it to stdout.
	}

	void visitData(std::vector<const IData*>& v) override
	{
		cout << v[0]->getIdentifier() << " " << v[1]->getIdentifier() << endl;
	}
};

// example of a Strategy pattern.
// traverses the tree by level.
class MyQueryStrategy : public SpatialIndex::IQueryStrategy
{
private:
	queue<id_type> ids;

public:
	void getNextEntry(const IEntry& entry, id_type& nextEntry, bool& hasNext) override
	{
		IShape* ps;
		entry.getShape(&ps);
		Region* pr = dynamic_cast<Region*>(ps);

		cout << pr->m_pLow[0] << " " << pr->m_pLow[1] << endl;
		cout << pr->m_pHigh[0] << " " << pr->m_pLow[1] << endl;
		cout << pr->m_pHigh[0] << " " << pr->m_pHigh[1] << endl;
		cout << pr->m_pLow[0] << " " << pr->m_pHigh[1] << endl;
		cout << pr->m_pLow[0] << " " << pr->m_pLow[1] << endl << endl << endl;
			// print node MBRs gnuplot style!

		delete ps;

		const INode* n = dynamic_cast<const INode*>(&entry);

		// traverse only index nodes at levels 2 and higher.
		if (n != nullptr && n->getLevel() > 1)
		{
			for (uint32_t cChild = 0; cChild < n->getChildrenCount(); cChild++)
			{
				ids.push(n->getChildIdentifier(cChild));
			}
		}

		if (! ids.empty())
		{
			nextEntry = ids.front(); ids.pop();
			hasNext = true;
		}
		else
		{
			hasNext = false;
		}
	}
};
class MyQueryStrategy2 : public IQueryStrategy
{
public:
	Region m_indexedSpace;

public:
	void getNextEntry(const IEntry& entry, id_type& /* nextEntry */, bool& hasNext) override
	{
		// the first time we are called, entry points to the root.

		// stop after the root.
		hasNext = false;

		IShape* ps;
		entry.getShape(&ps);
		ps->getMBR(m_indexedSpace);
		delete ps;
	}
};

int main(int argc, char** argv)
{
	try
	{
		if (argc != 7)
		{
			std::cerr << "Usage: " << argv[0] << " input_file query_file capacity utilization dimension k." << std::endl;
			return -1;
		}
		std::ifstream fin(argv[2]);
		if (! fin)
		{
			cerr << "Cannot open query file " << argv[1] << "." << endl;
			return -1;
		}
		int k = atoi(argv[6]);
		int dim = atoi(argv[5]);
		double utilization = atof(argv[4]);
		int capacity=atoi(argv[3]);
		// IStorageManager* diskfile = StorageManager::createNewMemoryStorageManager(baseName, 4096);
		IStorageManager* diskfile = StorageManager::createNewMemoryStorageManager();
			// Create a new storage manager with the provided base name and a 4K page size.

		StorageManager::IBuffer* file = StorageManager::createNewRandomEvictionsBuffer(*diskfile, 10, false);
			// applies a main memory random buffer on top of the persistent storage manager
			// (LRU buffer, etc can be created the same way).

		MyDataStream stream(argv[1]);

		// Create and bulk load a new RTree with dimensionality dim, using "file" as
		// the StorageManager and the RSTAR splitting policy.
		id_type indexIdentifier;
		ISpatialIndex* tree = RTree::createAndBulkLoadNewRTree(
			RTree::BLM_STR, stream, *file, utilization, capacity, capacity, dim, SpatialIndex::RTree::RV_RSTAR, indexIdentifier);
		size_t count = 0;
		size_t indexIO = 0;
		size_t leafIO = 0;
		id_type id;
		uint32_t op;
		double x1, x2;
		double plow[dim], phigh[dim];
		cerr<< std::flush;
		cerr<< "The tree has been made. Answering the queries.\n\n";

		while (fin)
		{
			fin >> op >> id ;
			// fin >> x1 >> y1 >> x2 >> y2;
			
			if (! fin.good()) continue; // skip newlines, etc.

			if (op == QUERY)
			{
				for (int i = 0; i < dim; i++)
					fin >> plow[i];
				for (int i = 0; i < dim; i++)
					fin >> phigh[i];
				MyVisitor vis;
				Point p = Point(plow, dim);
				tree->nearestNeighborQuery(k, p, vis);
				indexIO += vis.m_indexIO;
				leafIO += vis.m_leafIO;
					// example of the Visitor pattern usage, for calculating how many nodes
					// were visited.
			}
			else
			{
				std::cerr << "This is not a query operation." << endl;
			}

			if ((count % 1000) == 0) cerr << count << endl;

			count++;
		}

		MyQueryStrategy2 qs;
		tree->queryStrategy(qs);

		cerr << "Indexed space: " << qs.m_indexedSpace << endl;
		cerr << "Operations: " << count << endl;
		cerr << "---------Tree--------\n";
		cerr << *tree;
		cerr << "---------Tree End--------\n";
		cerr << "Index I/O: " << indexIO << endl;
		cerr << "Leaf I/O: " << leafIO << endl;
		cerr << "Buffer hits: " << file->getHits() << endl;

		// std::cerr << *tree;
		// std::cerr << "Buffer hits: " << file->getHits() << std::endl;
		std::cerr << "Index ID: " << indexIdentifier << std::endl;

		// bool ret = tree->isIndexValid();
		// if (ret == false) std::cerr << "ERROR: Structure is invalid!" << std::endl;
		// else std::cerr << "The stucture seems O.K." << std::endl;


		delete tree;
		delete file;
		delete diskfile;
			// delete the buffer first, then the storage manager
			// (otherwise the the buffer will fail trying to write the dirty entries).
	}
	catch (Tools::Exception& e)
	{
		std::cerr << "******ERROR******" << std::endl;
		std::string s = e.what();
		std::cerr << s << std::endl;
		return -1;
	}
	catch (...)
	{
		cerr << "******ERROR******" << std::endl;
		cerr << "other exception" << std::endl;
		return -1;
	}
	return 0;
}
