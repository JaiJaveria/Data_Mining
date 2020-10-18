#include <iostream>
#include <queue>
#include "FPNode.h"
using namespace std;
	FPNode::FPNode(int k) : children()
	{
		parent=NULL;
		counter=0;
		key=k;
		next=NULL;
	}
	void FPNode::findKey(int a )
	{
		if(key==a)
		{
			cout << "22N Found "<< a<<"\n";
			return;
		}
		for(auto i: children)
		{
			i.second->findKey(a);
		}
	}

	void FPNode::insert(std::vector<int> v, int c, int i, unordered_map<int,int> *&frequency )
	{
		int k=v[i];
		if((frequency)->find(k)!=(frequency)->end()){
			(*frequency)[k]+=c;
			}
		else{
			(*frequency)[k]=c;
		}

		FPNode *n;
		if(children.find(k)!=children.end())
		{
			children[k]->counter+=c;

		}
		else
		{

			n= new FPNode(k);
			n->counter+=c;
			n->parent=this;
			this->children[k]=n;
		}
		if(i+1<v.size()){
			children[k]->insert(v,c,i+1, frequency);}
	}
	void FPNode::insert(std::vector<pair<int,int>> v, int c, int i, std::vector<pair<int,FPNode*>> *endNode,unordered_map<int,int> *indexFind, unordered_map<int,int> *frequency )
	{
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
		if(children.empty())
		{
			ret.first=this;
			ret.second=this;
			return ret;
		}
		bool b=false;
		for(auto i:children)
		{
			ret=i.second->buildLeafList();
			if(!b)
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
		while(!q.empty())
		{
			FPNode* n= q.front();
			q.pop();
			printf("%d:%d ",n->key,n->counter );
			for(auto i: n->children)
			{
				q.push(i.second);
			}
		}
		printf("\n");
	}
