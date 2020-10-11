// #include "FPNode.cpp"
#include "FPTree.cpp"

#include <fstream> //for ifstream
#include <utility> //fOR pair
#include <vector> 
#include <iostream>
#include <algorithm> //for sort
#include <sstream> //for istringstream
using namespace std;
bool compare(pair<int,unsigned int> a, pair<int,unsigned int> b )
{
	//more count more
	return ((a.second > b.second) || (a.second==b.second && a.first > b.first));
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
	cout << argv[1]<<"\n";
	// cout << argv[2] << "\n";
	// printf("aaaa\n");
	// cout <<"aaa";
	// cout << "28--";
	// cout << "28";
	// cout << endl;
	datb.open(argv[1]);
	if(!datb)
	{
		cout << "Not found";
		return -1;
	}
	// cout << "35--";
	// cout << endl;

	int data;
	string d;
	vector<pair<int,unsigned int>> freq;//to store the counters.
	pair<int, unsigned int> p(0,0);
	freq.push_back(p);
	int item=1;
	numT=0;
	int c=0;//delete
	// cout << "43--";
	// cout << endl;

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
	float s=x*numT/100;
	cout << s << endl;
	// sort(freq.begin(), freq.end(), compare);
	// // now remove the infrequent ones.
	// while(freq.back().second<s)
	// {
	// 	freq.pop_back();
	// }
	// // for testing. outputting the frequent item list
	// for (int i = 0; i < freq.size(); ++i)
	// 	cout << freq[i].first << " : " << freq[i].second << "\n";

	//make hash table of frequent ones
	for (int i = 0; i < freq.size(); ++i)
	{
		if(freq[i].second>=s)
		{
			freqSin[freq[i].first]=freq[i].second;
		}
	}
	for (auto i : freqSin)
	{
		/* code */
		cout << i.first << " : "<< i.second << endl;
	}
	freq.clear();
	ifstream datbA;
	datbA.open(argv[1]);
	if(!datbA)
	{
		cout << "Not found";
		return -1;
	}
	std::vector<pair<int,int>> basket;
	FPTree FP_tree;
	// cout << "93--";
	cout << endl;

	c=0;//need to delete
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
			
			// cout << basket.size();
			FP_tree.insert(basket,1);
			cout << "112--";
			cout << endl;
			for (int i = 0; i < basket.size(); ++i)
			{
				cout << basket[i].first << " ";
			}
			cout << endl;

			cout << "141--";
			cout << endl;
			FP_tree.print();
			
		}
		
	}
	
	return 0;
}