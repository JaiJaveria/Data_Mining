#include <unordered_map> 
#include <vector>
#include <iostream>
using namespace std;
class FPNode
{
public:
	FPNode(int k) : children()
	// FPNode(int k) 
	{
		parent=NULL;
		counter=0;
		key=k;
		next=NULL;
	}
	FPNode* parent;
	FPNode* next;
	int key;
	int counter;
	unordered_map<int,FPNode*> children;
	

	void insert(std::vector<int> v, int c, int i)
	{
		int k=v[i];
		FPNode *n;
		if(children.find(k)!=children.end())
			children[key]->counter+=c;
		else
		{
			n= new FPNode(k);
			n->counter+=c;
			n->parent=this;
			this->children[key]=n;

			
		}
		if(i+1<v.size()){
			children[k]->insert(v,c,i+1);}
	}
	void insert(std::vector<pair<int,int>> v, int c, int i, std::vector<pair<int,FPNode*>> *endNode,unordered_map<int,int> *indexFind )
	// void insert(std::vector<pair<int,int>> v, int c, int i,std::vector<pair<int,FPNode*>> *header,std::vector<pair<int,FPNode*>> *endNode, unordered_map<int,int> *indexFind )
	{
		// cout<< "37FPN" << endl;
		// cout<< v.size()<< endl;
		int key=v[i].first;
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
			(this->children[key])->insert(v,c, i+1, endNode, indexFind);
	}
	// ~FPNode();
	
};