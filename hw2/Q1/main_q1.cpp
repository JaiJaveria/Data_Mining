#include<iostream>
#include<bits/stdc++.h>
#include <random>
#include <chrono>
#include <cmath>

#define FOR(i,n) for(int i=0; i<n; i++)
#define abs(x,y) (x>=y) ? x-y : y-x
#define dataset_size 1000000

using namespace std;


class Random{
public:
	mt19937_64 rng;
    Random(mt19937_64 rng1){
	    this->rng=rng1;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    	seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    	rng.seed(ss);
    }
};

void generate_dateset(vector<vector<double>> &dataset, int d){

	mt19937_64 rng;
	uniform_real_distribution<double> unif(0, 1);
	Random* random = new Random(rng);

	FOR(i,dataset_size){
		vector<double> tmp={};
		FOR(j,d){
			tmp.push_back( unif(random->rng) );
		}
		dataset.push_back(tmp);
	}
}

void generate_queries(unordered_set<int> &queries){
	while(queries.size() <= 100){
		queries.insert(rand()%dataset_size);
	}
}

double norm(vector<double> d1, vector<double> d2, int idx){
	double ans=0;
	int d=d1.size();
	if(idx==1){
		FOR(i,d){
			ans+=abs(d1[i],d2[i]);
		}
	}
	else if(idx==2){
		FOR(i,d){
			double d=abs(d1[i],d2[i]);
			ans+=d*d;
		}
		ans=sqrt(ans);
	}
	else{
		FOR(i,d){
			double d=abs(d1[i],d2[i]);
			if(d > ans) ans = d;
		}
	}
	return ans;
}

double norm_ratio(vector<vector<double>> &dataset, int index, int idx){
	vector<double> query = dataset[index];
	int d=query.size();
	int n=dataset.size();
	double min=INT_MAX, max=0;
	FOR(i,n){
		if(i!=index){
			double norm1 = norm(dataset[i], query, idx);
			if(norm1 < min) min=norm1;
			if(norm1 > max) max = norm1;
		}
	}
	return max/min;
}


int main(int argc,  char* argv[]){

	int d=stoi(argv[1]);

	int which=stoi(argv[2]);

	vector<vector<double>> dataset;
	generate_dateset(dataset,d);

	unordered_set<int> queries;
	generate_queries(queries);

	double avg=0;
	for(int x: queries){
		avg+=norm_ratio(dataset, x, which);
	}
	cout<<(avg/100);
	return 0;
}
