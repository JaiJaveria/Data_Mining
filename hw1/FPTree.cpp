#include "FPNode.cpp"
#include <queue>
#include "FPNode.h"

// #include <iostream>
class FPTree
{
public:
	FPTree()
	{
		root= new FPNode(-1);
	}
	// ~FPTree()
	// {
	// 	delete root;
	// }
	FPNode *root;

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
		// cout << "\n";
	}
};