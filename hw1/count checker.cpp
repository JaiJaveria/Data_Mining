#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	ifstream datb;
datb.open(argv[1]);
if(!datb)
{
	cout << "Not found";
	return -1;
}
string d;
int data;
std::vector<unordered_set<int>> m;
std::vector<std::vector<int>> v;//{121,8,122}	;
std::vector<int> vec;//{121,8,122}	;
v.push_back({121,8,122});
m.push_back(unordered_set<int>());
v.push_back({121,8});
m.push_back(unordered_set<int>());
v.push_back({121,122});
m.push_back(unordered_set<int> ());
v.push_back({121});
m.push_back(unordered_set<int> ());
std::vector<int> c(v.size(),0);
// int c=0;
int t=0;
while(getline(datb, d))
{
	t++;
	istringstream ss(d);
	vec.clear();
	while (ss >> data)
		{
			vec.push_back(data);
		
		}
	for (int j = 0; j < v.size(); ++j)
	{
		m[j].clear();

		for(auto k:vec)
		{
			m[j].insert(k);
		}
		bool b=true;
		for(auto i:v[j])
		{
			if(m[j].find(i)==m[j].end())
			{
				b=false;
				break;

			}
		}

		if(b)
			c[j]++;
		/* code */
	}
	

}
	cout << "Total Transactions : "<< t<< endl;

cout << "The sequence\n";
for (int j = 0; j < v.size(); ++j)
{

	/* code */
	for(auto i:v[j])
	{
		cout << i<< " ";
	}
	cout <<endl;
	cout << "Count : "<< c[j]<< endl;
	/* code */
}

	return 0;
}

