#include "FPNode.cpp"
#include <queue>
#include "FPNode.h"
class FPTree
{
public:
	FPTree()
	{
		root= new FPNode(-1);
	}

	FPNode *root;
	void findKey(int a)
	{
		for(auto i: root->children)
		{
			i.second->findKey(a);
		}
	}
	void insert(std::vector<int> v, int c,unordered_map<int,int> *&frequency  )
	{
		root->insert(v, c, 0, frequency);
	}
	void insert(std::vector<pair<int,int>> v, int c,std::vector<pair<int,FPNode*>> *endNode, unordered_map<int,int> *indexFind, unordered_map<int,int> *frequency )
	{
		root->insert(v, c, 0,endNode, indexFind ,frequency);
	}
	FPNode* buildLeafList()
	{

		return (root->buildLeafList()).first;
	}
	
	void print()
	{
		queue<FPNode*> q;
		q.push(root);
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
};