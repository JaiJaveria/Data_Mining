#include "FPNode.cpp"
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
	/* Reading the dat file */
	ifstream datb;
	int numT;
	unordered_map<int, int> freqSin;//frequent singletons
	//first argument is the path of database and second is the threshold percentage.
	int x=atoi(argv[2]);
	// cout << argv[1]<<"\n";
	// cout << argv[2] << "\n";

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
	// sort(freq.begin(), freq.end(), compare);
	// // now remove the infrequent ones.
	// while(freq.back().second<s)
	// {
	// 	freq.pop_back();
	// }
	// for testing. outputting the frequent item list
	// for (int i = 0; i < freq.size(); ++i)
	// 	cout << freq[i].first << " : " << freq[i].second << "\n";

	//make hash table of freqent ones
	for (int i = 0; i < freq.size(); ++i)
	{
		
		if(freq[i].second>=s)
		{
			freqSin[freq[i].first]=freq[i].second;
		}
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
		sort(basket.begin(), basket.end(), compare);
		// for (int i = 0; i < basket.size(); ++i)
		// {
		// 	cout << basket[i].first << " ";
		// }
		// cout << "\n";
		
	}
	return 0;
}