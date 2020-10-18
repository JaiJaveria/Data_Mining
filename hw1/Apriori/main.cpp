#include<iostream>
#include<bits/stdc++.h>
#include<set>


using namespace std;

bool valid(set<string> s1, set<string> s2){

	if(s1.size()!=s2.size()) return false;
	set<string>::iterator t1 = s1.end(); t1--;
	set<string>::iterator t2 = s2.end(); t2--;
	s1.erase(t1);
	s2.erase(t2);
	return s1==s2;
}

bool prune( set<set<string>> &F, set<string> c){
	for(set<string>::iterator i=c.begin(); i!=c.end(); i++){
		// set<int> s=c;
		c.erase(i);
		if(F.find(c) == F.end()) {return true;}
		c.insert(*i);
	}
	return false;
}


void candidate( set<set<string>> &F, map < set<string>,int > &C){
	for(set<set<string>>::iterator i=F.begin(); i!=F.end(); i++) {
		set<set<string>>::iterator j=i;
		j++;
		for(; j!=F.end(); j++){
			if(valid(*i, *j)){
				set<string> s = *i;
				set<string>::iterator k = (*j).end();
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





void parse(string &line, set<string> &v){
  string sample="";
  int n=line.size();
  for(int i=0;i<n;i++){
      if(line[i]==' '){
          if(sample!=""){
              v.insert((sample));
              sample="";
          }
      }
      else{
          sample+=line[i];
      }
  }
  // residual string process
  if(sample!=""){
      v.insert((sample));
  }
}

int main(int argc,  char* argv[]){

	ofstream debugOut;
      string file = string(argv[1]);

	string debFile = string(argv[3]);
	debugOut.open(debFile.c_str());

      ifstream freader(file);
      if(!freader.is_open()){
          cout<<"input file not opened"<<endl;
          return -2;
      }
      string line;
      map < set<string>,int > C;
	int T=0;
	int max_item=0;
      while(getline(freader,line)){
		T++;
        	set<string> v;
        	parse(line,v);
		for(string const &x: v) {
			set<string> s1={x};
			C[s1]++;
		}
      }

	freader.close();

	float support = (stof(argv[2])/100)*T;
	set< set<string> > F;
	// for(auto const &x: C)
	for(map < set<string>,int >::iterator it=C.begin(); it!=C.end(); it++){
		if((*it).second >= support) F.insert((*it).first);
	}

	vector< set<set<string>> > ans;
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
	        	set<string> t;
	        	parse(line,t);
			for(map < set<string>,int >::iterator it=C.begin(); it!=C.end(); it++){
				if (includes(t.begin(), t.end(), (*it).first.begin(), (*it).first.end())) (*it).second++;
			}
	      }
		freader1.close();
		F.clear();
		for(map < set<string>,int >::iterator it=C.begin(); it!=C.end(); it++){
			if((*it).second >= support) F.insert((*it).first);
		}
		if(F.size() !=0 ) ans.push_back(F);
	}

	for(const set<set<string>>& f: ans){
		for(const set<string>& e: f){
			for(const string& x: e) {debugOut<<x<<" ";}
			debugOut<<endl;
		}
	}
	return 0;



}
