#include <unordered_map> 
using namespace std;
class FPNode
{
public:
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
	
	// ~FPNode();
	
};