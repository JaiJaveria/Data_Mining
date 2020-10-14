#include<iostream>
#include<bits/stdc++.h>
#include<set>


using namespace std;


//checks if two sets have same size n, with first n-1 elements the same (for candidate_gen function)
bool valid(set<int> s1, set<int> s2){

	if(s1.size()!=s2.size()) return false;
	auto t1 = s1.end(); t1--;
	auto t2 = s2.end(); t2--;
	s1.erase(t1);
	s2.erase(t2);
	return s1==s2;
}

//returns true if pruning has to be done
bool prune( set<set<int>> &F, set<int> c){
	for(auto i=c.begin(); i!=c.end(); i++){
		// set<int> s=c;
		c.erase(i);
		if(F.find(c) == F.end()) {return true;}
		c.insert(*i);
	}
	return false;
}

//generates candidates Ck
void candidate( set<set<int>> &F, map < set<int>,int > &C){
	for(auto i=F.begin(); i!=F.end(); i++) {
		auto j=i;
		j++;
		for(; j!=F.end(); j++){
			if(valid(*i, *j)){
				set<int> s = *i;
				auto k = (*j).end();
				k--;
				s.insert(*k);
				if( !prune(F,s) ){
					C[s]=0;
				}
			}
			else break;
		}
	}
}




//parses an input string of integers into integers and stores them in set v
void parse(string &line, set<int> &v){
  string sample="";
  int n=line.size();
  for(int i=0;i<n;i++){
      if(line[i]==' '){
          if(sample!=""){
              v.insert(stoi(sample));
              sample="";
          }
      }
      else{
          sample+=line[i];
      }
  }
  // residual string process
  if(sample!=""){
      v.insert(stoi(sample));
  }
}

//drives the implementation and applies apriori algorithm
int main(int argc,  char* argv[]){

      string file = string(argv[1]);
      ifstream freader(file);
      if(!freader.is_open()){
          cout<<"input file not opened"<<endl;
          return -2;
      }
      string line;
      map < set<int>,int > C;
	int T=0;
	int max_item=0;
      while(getline(freader,line)){
		T++;
        	set<int> v;
        	parse(line,v);
		for(auto const &x: v) {
			set<int> s1={x};
			C[s1]++;
		}
      }

	freader.close();

	float support = (stof(argv[2])/100)*T;
	set< set<int> > F;
	for(auto const &x: C) {
		if(x.second >= support) F.insert(x.first);
	}

	vector< set<set<int>> > ans;
	ans.push_back(F);

	while(F.size() != 0){
		C.clear();
		candidate(F,C);
		// for(auto &c: C){
		// 	for(int x: c.first) cout<<x<<" ";
		// 	cout<<": "<<c.second<<endl;
		// }
		ifstream freader1(file);
		if(!freader1.is_open()){
	          cout<<"input file not opened"<<endl;
	          return -2;
	      }
		while(getline(freader1,line)){
	        	set<int> t;
	        	parse(line,t);
			for(auto &c: C) {
				if (includes(t.begin(), t.end(), c.first.begin(), c.first.end())) c.second++;
			}
	      }
		freader1.close();
		F.clear();
		for(auto const &x: C) {
			if(x.second >= support) F.insert(x.first);
		}
		if(F.size() !=0 ) ans.push_back(F);
	}

	for(const set<set<int>>& f: ans){
		for(const set<int>& e: f){
			for(const int& x: e) {cout<<x<<" ";}
			cout<<endl;
		}
	}
	return 0;



}
