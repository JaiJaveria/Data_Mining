#include <unordered_map> 
#include <vector>
#include <iostream>
using namespace std;
class FPNode
{
public:
	// FPNode(int k) : children()
	FPNode(int k) 
	{
		parent=NULL;
		counter=0;
		key=k;
	}
	FPNode* parent;
	int key;
	int counter;
	unordered_map<int,FPNode*> children;
	

	void insert(std::vector<int> v, int c, int i)
	{
		int key=v[i];
		// FPNode fpn;
		FPNode *n;
		if(children.find(key)!=children.end())
		{
			children[key]->counter+=c;
		}
		else
		{
			FPNode fpn= FPNode(key);
			n=&fpn;
			children[key]=n;
			n->counter+=c;
			n->parent=this;
		}
		// cout <<"3" << (children[key]==n)<< endl;
		if(i+1<v.size())
			// children[key]->insert(v,c, i+1);
			children[key]->insert(v,c, i+1);
	}
	void insert(std::vector<pair<int,int>> v, int c, int i)
	{
		cout<< "37FPN" << endl;
		cout<< v.size()<< endl;
		int key=v[i].first;
		FPNode *n;
		if(!this->children.empty())
		{
			if(this->children.find(key)!=this-> children.end())
			{
				this->children[key]->counter+=c;
			}
			else
			{
				n= new FPNode(key);
				// FPNode fpn= new FPNode(key);
				// n=&fpn;
				// cout << (n==NULL)<< endl;
				this->children[key]=n;
				n->counter+=c;
				n->parent=this;
				cout << n << endl;
				cout << (this->children[key]==n)<< endl;
			}	
		}	
		
		// cout << (children==NULL)<< endl; 
			cout << this->children[key] << endl;

		if(i+1<v.size())
			this->children[key]->insert(v,c, i+1);
	}
	// ~FPNode();
	
};