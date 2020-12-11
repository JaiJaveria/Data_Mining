#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <string>
#include <algorithm>
//from https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}
int main(int argc, char const *argv[])
{
	ifstream o1;
	unordered_set<string> m;
	o1.open(argv[1]);
	string s;
	while(getline(o1,s))
	{
		s=trim(s);
		m.insert(s);
	}
	o1.close();
	o1.open(argv[2]);
	while(getline(o1,s))
	{
		s=trim(s);
		if(m.find(s)==m.end())
			cout <<s<<"\n";
	}
	return 0;
}