#include "FPNode.cpp"
#include <queue>
// #include <iostream>
class FPTree
{
public:
	FPTree()
	{
		root= new FPNode(-1);
	}
	FPNode *root;

	void insert(std::vector<int> v, int c )
	{
		root->insert(v, c, 0);
	}
	void insert(std::vector<pair<int,int>> v, int c )
	{
		root->insert(v, c, 0);
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
			printf("%d:%d ",n->key,n->counter2 );
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