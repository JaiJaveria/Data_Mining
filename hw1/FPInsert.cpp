#include "FPTree.cpp"
#include "cond_fp.cpp"

#include <fstream> //for ifstream
#include <utility> //fOR pair
#include <vector> 
#include <iostream>
#include <algorithm> //for sort
#include <sstream> //for istringstream
#include <functional> // for bind

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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	/* Reading the dat file */
	ifstream datb;
	int numT;
	unordered_map<int, int> freqSin;//frequent singletons
	//first argument is the path of database and second is the threshold percentage.
	int x=atoi(argv[2]);
	datb.open(argv[1]);
	if(!datb)
	{
		cout << "Not found\n";
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
	
	//------------make hash table of frequent ones
	for (int i = 0; i < freq.size(); ++i)
		if(freq[i].second>=s && freq[i].second>0 )
			freqSin[freq[i].first]=freq[i].second;
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
	//-----header and endnode created
	//---- read the datab and create fptree
	ifstream datbA;
	datbA.open(argv[1]);
	if(!datbA)
	{
		cout << "Not found";
		return -1;
	}
	unordered_map <int,int> frequency;
	while(getline(datbA, d))
	{
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
			
		}
	}
	
	FPNode* con_fp;
	std::vector<int> v;
	unordered_map<int,int> conFreq;
	std::vector<int> order;
	//-----------------------
	// now  doing conditional fptree here and mining frequent subsets
	for (int i = 0; i < header.size(); ++i)
		order.push_back(header[i].first);
	for (int i = header.size()-1; i >=0; --i)
	{
		cout << header[i].first <<"\n";//printing singleton.
		order.pop_back();//the last element is not required in the analysis
		conFreq.clear();
		con_fp=cond_fp(header[i].second, NULL, &conFreq, header[i].first);
		v.clear();
		v.push_back(header[i].first);
		mineFreq(con_fp, &conFreq, &order, &v, s);
		//see the links of each header entry and find frequent itemsets
	}

	delete FP_tree.root;
	return 0;
}