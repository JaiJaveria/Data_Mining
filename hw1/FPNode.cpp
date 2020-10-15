// #include <unordered_map> 
// #include <vector>
#include <iostream>
#include <queue>
#include "FPNode.h"
using namespace std;
// class FPNode
// {
// public:
	FPNode::FPNode(int k) : children()
	// FPNode(int k) 
	{
		parent=NULL;
		counter=0;
		key=k;
		next=NULL;
	}
	// FPNode* parent;
	// FPNode* next;
	// int key;
	// int counter;
	// unordered_map<int,FPNode*> children;

	void FPNode::insert(std::vector<int> v, int c, int i, unordered_map<int,int> *&frequency )
	{
		int k=v[i];
		// cout << "27N"<<endl;
		// cout << key<<endl;
		if((frequency)->find(k)!=(frequency)->end()){
			(*frequency)[k]+=c;
			}
		else{
			(*frequency)[k]=c;
		}
		// cout << "35N"<<endl;

		FPNode *n;
		if(children.find(k)!=children.end())
		{
			// cout << "41N"<<endl;
			children[k]->counter+=c;

		}
		else
		{
			// cout << "42N"<<endl;

			n= new FPNode(k);
			n->counter+=c;
			n->parent=this;
			this->children[k]=n;
		}
		// cout << "49N"<<endl;

		// cout<< v.size();
		// cout << '\n'<<i;
		// cout << endl;
		if(i+1<v.size()){
			children[k]->insert(v,c,i+1, frequency);}
	}
	void FPNode::insert(std::vector<pair<int,int>> v, int c, int i, std::vector<pair<int,FPNode*>> *endNode,unordered_map<int,int> *indexFind, unordered_map<int,int> *frequency )
	// void insert(std::vector<pair<int,int>> v, int c, int i,std::vector<pair<int,FPNode*>> *header,std::vector<pair<int,FPNode*>> *endNode, unordered_map<int,int> *indexFind )
	{
		// cout<< "37FPN" << endl;
		// cout<< v.size()<< endl;
		int key=v[i].first;
		if((*frequency).find(key)!=(*frequency).end()){
			(*frequency)[key]+=c;
			}
		else{
			(*frequency)[key]=c;
			
		}
		FPNode *n;
		if((this->children).find(key)!=(this-> children).end())
			(this->children[key])->counter+=c;
		else
		{
			n= new FPNode(key);
			n->counter+=c;
			n->parent=this;
			this->children[key]=n;
			int i=(*indexFind)[key];
			if ((*endNode)[i].second!=NULL)
				(*endNode)[i].second->next=this->children[key];	
			(*endNode)[i].second=this->children[key];

		}	
		if(i+1<v.size())
			(this->children[key])->insert(v,c, i+1, endNode, indexFind,frequency);
	}
	pair<FPNode*, FPNode*> FPNode::buildLeafList()
	{
		pair<FPNode*,FPNode*> ret;
		FPNode* first;
		FPNode* last=NULL;
		// cout <<"91N-key\n";
		// cout << key;
		// cout << endl;
		if(children.empty())
		{
			//check this
			ret.first=this;
			ret.second=this;
			return ret;
		}
		// else
		// {
			bool b=false;
			for(auto i:children)
			{
				ret=i.second->buildLeafList();
				if(!b)//
				{	
					b=true;
					first=ret.first;
				}
				if(last!=NULL)
				{
					last->next=ret.first;

				}
				last=ret.second;
			}
		// }
		ret.first=first;
		ret.second=last;
		return ret;
	}
	FPNode::~FPNode()
	{
		for (auto i : children)
		{
			delete i.second;
		}
	}
	void FPNode::printT()
	{
		FPNode* r=this;
		while(r->parent!=NULL)
		{
			r=r->parent;
		}
		queue<FPNode*> q;
		q.push(r);
		// q.push(NULL);
		while(!q.empty())
		{
			FPNode* n= q.front();
			q.pop();
			// if(n==NULL)
				// cout << "\n";
			// else
			printf("%d:%d ",n->key,n->counter );
			// cout << n->key << " ";
			// for(auto i=n.children.begin(), i< n.children.end(); i++)
			for(auto i: n->children)
			{
				q.push(i.second);
			}
		}
		printf("\n");
	}
// };