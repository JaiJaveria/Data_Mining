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
	}
	FPNode* parent;
	int key;
	int counter;
	unordered_map<int,FPNode*> children;
	

	void insert(std::vector<int> v, int c, int i)
	{
		int k=v[i];
		//cout<<key<<endl;
		// FPNode fpn;
		//FPNode *n;
		
		
		if(children.find(k)!=children.end())
		{
			children[key]->counter+=c;

		}
		else
		{
			
			FPNode *n= new FPNode(k);
			
			//n=&fpn;
			
			children.insert({k,n});
			
			n->counter+=c;
			n->parent=this;
			
		}
		// cout <<"3" << (children[key]==n)<< endl;
		if(i+1<v.size()){
			// children[key]->insert(v,c, i+1);
			
			FPNode *a = (children[k]);
			a->insert(v,c,i+1);}
	}
	void insert(std::vector<pair<int,int>> v, int c, int i)
	{
		// cout<< "37FPN" << endl;
		// cout<< v.size()<< endl;
		int key=v[i].first;
		FPNode *n;
			if((this->children).find(key)!=(this-> children).end())
			{
				(this->children[key])->counter+=c;
				// cout << "55--";

			}
			else
			{
				n= new FPNode(key);
				// FPNode fpn= new FPNode(key);
				// n=&fpn;
				// cout << (n==NULL)<< endl;
				n->counter+=c;
				n->parent=this;
				this->children[key]=n;

				// cout << n << endl;
				// cout << (this->children[key]==n)<< endl;
			}	
		if(i+1<v.size())
			(this->children[key])->insert(v,c, i+1);
	}
	// ~FPNode();
	
};