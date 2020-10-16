// #include "FPNode.cpp"
#include "FPTree.cpp"
#include "cond_fp.cpp"

#include <fstream> //for ifstream
#include <utility> //fOR pair
#include <vector> 
#include <iostream>
#include <algorithm> //for sort
#include <sstream> //for istringstream
#include <functional> // foor bind
using namespace std;
using namespace std::placeholders;
bool compare(pair<int,unsigned int> a, pair<int,unsigned int> b )
{
	//more count more
	return ((a.second > b.second) || (a.second==b.second && a.first > b.first));
}
bool compareMap(unordered_map<int, int> *m, pair<int,FPNode*> a, pair<int,FPNode*> b )
{
	//more count more
	return (((*m)[a.first] > (*m)[b.first]) || ((*m)[a.first]==(*m)[b.first] && a.first > b.first));
}


int main(int argc, char const *argv[])
{
	cout << boolalpha;
	/* Reading the dat file */
	ifstream datb;
	int numT;
	unordered_map<int, int> freqSin;//frequent singletons
	//first argument is the path of database and second is the threshold percentage.
	int x=atoi(argv[2]);
	datb.open(argv[1]);
	if(!datb)
	{
		cout << "Not found";
		return -1;
	}

	int data;
	string d;
	vector<pair<int,unsigned int>> freq;//to store the counters.
	pair<int, unsigned int> p(0,0);
	freq.push_back(p);
	int item=1;
	numT=0;
	while(getline(datb, d))
	{
		numT++;
		// c++;//delete
		// if(c>3)
			// break;
		istringstream ss(d);
		while( ss>> data)
		{
			if(data >=item)
			{
				while(item <= data)
				{
					pair<int, unsigned int> p(item,0);
					freq.push_back(p);
					item++;
				}
			}
			freq[data].second++;
		}
	}
	float s=(float)x*numT/100;
	// cout <<"70--threshold "<< s << endl;
	//sorting the whole frequent table
	// sort(freq.begin(), freq.end(), compare);
	// // now remove the infrequent ones.
	// while(freq.back().second<s)
	// {
	// 	freq.pop_back();
	// }
	// // for testing. outputting the frequent item list
	// for (int i = 0; i < freq.size(); ++i)
	// 	cout << freq[i].first << " : " << freq[i].second << "\n";

	//------------make hash table of frequent ones
	for (int i = 0; i < freq.size(); ++i)
		if(freq[i].second>=s && freq[i].second>0 )
			freqSin[freq[i].first]=freq[i].second;

	// cout << "86-- hashmap";
	// for (auto i : freqSin)
	// 	cout << i.first << " : "<< i.second << endl;

	freq.clear();
	//------------hash table created. 
	//------------now make the header file
	std::vector<pair<int,int>> basket;
	FPTree FP_tree;
	std::vector<pair<int,FPNode*>> header;
	std::vector<pair<int,FPNode*>> endNode;
	bool headerInit=false;
	//indexfind to find the index of a item id in header vector.
	unordered_map<int, int> indexFind;
	auto compBind=bind(compareMap, &freqSin, _1, _2 );
	for(auto i: freqSin)
	{
		pair<int,FPNode*> p(i.first,NULL);
		header.push_back(p);
	}
	sort(header.begin(), header.end(), compBind);
	endNode.assign(header.begin(), header.end());
	for (int i = 0; i < header.size(); ++i)
		indexFind[header[i].first]=i;
	// //print the header
	// for (auto i: header)
	// 	cout << i.first << endl;
	// cout << endl;
	// for (auto i: endNode)
	// 	cout << i.first << endl;
	//-----header and endnode created
	//---- read the datab and create fptree
	ifstream datbA;
	datbA.open(argv[1]);
	if(!datbA)
	{
		cout << "Not found";
		return -1;
	}
	int c=0;//need to delete
	unordered_map <int,int> frequency;
	while(getline(datbA, d))
	{
		c++;//delete
		if(c>64)
			break;
		basket.clear();
		istringstream ss(d);
		while( ss>> data)
		{
			if(freqSin.find(data)!=freqSin.end())
			{
				pair<int,int> p(data,freqSin[data]);
				basket.push_back(p);
			}
		}
		if(basket.size()>0)
		{
			sort(basket.begin(), basket.end(), compare);
			FP_tree.insert(basket,1, &endNode, &indexFind , &frequency);
			if(!headerInit)
			{
				//insert only sets the end node. the end node initialized first time is the starting node of that element. thus we need to initialize that. when all the header is initialized we do not want to get in this loop.
				headerInit=true;
				for (int i = 0; i < header.size(); ++i)
				{
					if(endNode[i].second!=NULL && header[i].second==NULL)
						header[i].second=endNode[i].second;
					else if(endNode[i].second==NULL && header[i].second==NULL)
						headerInit=false;
				}
			}
			// cout<< "160I Header Print\n";
			// for (int i = 0; i < header.size(); ++i)
			// {
				// cout << header[i].first << " ";
			// }
			// cout << endl;
			// cout << "112--";
			// cout << endl;
			// for (int i = 0; i < basket.size(); ++i)
			// {
			// 	cout << basket[i].first << " ";
			// }
			// cout << endl;

			// cout << "141--";
			// cout << endl;
			// FP_tree.print();
		}
	}
	// //printing the final tree and header for debug purpose
	// cout << "174 FPTree--";
	// cout << endl;
	// FP_tree.print();
	// cout << "176 Header--" << endl;		
	// for( auto ih : header)
	// {
	// 	FPNode* j;
	// 	j=ih.second;
	// 	while(j!=NULL)
	// 	{
	// 		cout << j->key << ":"<<j->counter<< " ";
	// 		j=j->next;
	// 	}
	// 	cout <<endl;
	// }
	FPNode* con_fp;
	std::vector<int> v;
	unordered_map<int,int> conFreq;
	std::vector<int> order;
	//-----------------------
	// now  doing conditional fptree here and mining frequent subsets

	// cout << "195FPNI FP Tree Print--"<< endl;
	// FP_tree.print();
	// cout << endl;
	// cout<< "200I Header Print\n";
	
	for (int i = 0; i < header.size(); ++i)
	{
		// cout << header[i].first << " ";
		order.push_back(header[i].first);
		/* code */
	}
	// cout << endl;
	for (int i = header.size()-1; i >=0; --i)
	{
		cout << header[i].first <<"\n";//printing singleton.
		order.pop_back();//the last element is not required in the analysis
		conFreq.clear();
		con_fp=cond_fp(header[i].second, NULL, &conFreq);

		// cout << "214I LeafNodes Print\n";
		// FPNode *n=con_fp;
		// while(n!=NULL)
		// {
		// 	cout << n->key << " ";
		// 	n=n->next;
		// }
		// cout<<endl;
		// cout << "222I Cond. Tree Print\n";
		// con_fp->printT();
		// cout<<endl;
		// for (auto i: order)
		// {
		// 	cout << i <<" ";
		// }
		// cout << endl;

		v.clear();
		v.push_back(header[i].first);
		mineFreq(con_fp, &conFreq, &order, &v, s);

		// cout << "236I Cond. End of call to Mine Freq"<<endl;
		// cout << "238I Break encoutered"<<endl;
		// break;
		//see the links of each header entry and find frequent itemsets
	}
	return 0;
}