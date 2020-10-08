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
	//first argument is the path of database and second is the threshold percentage.
	int x=(int) argv[2];
	datb.open(argv[1]);
	if(!datb)
	{
		cout << "Not found";
		return -1;
	}
	else
	{
		int data;
		string d;
		vector<pair<int,unsigned int>> freq;//to store the counters.
		pair<int, unsigned int> p(0,0);
		freq.push_back(p);
		int item=1;
		int numT=0;
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
		sort(freq.begin(), freq.end(), compare);
		
		auto s=x*numT/100;
		while(freq.back().second<s)
		{
			freq.pop_back();
		}
		// for (int i = 0; i < freq.size(); ++i)
		// 	cout << freq[i].first << " : " << freq[i].second << "\n";
	}
	return 0;
}