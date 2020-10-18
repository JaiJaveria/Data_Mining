#ifndef FPNODE_H
#define FPNODE_H
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
class FPNode
{
private:
    int m_year;
    int m_month;
    int m_day;
 
public:
	FPNode* parent;
	FPNode* next;
	int key;
	int counter;
	FPNode(int k);
	~FPNode();
	unordered_map<int,FPNode*> children;
    void insert(std::vector<int> v, int c, int i, unordered_map<int,int> *&frequency );
    void insert(std::vector<pair<int,int>> v, int c, int i, std::vector<pair<int,FPNode*>> *endNode,unordered_map<int,int> *indexFind, unordered_map<int,int> *frequency );
	pair<FPNode*, FPNode*> buildLeafList();
	void printT();
	void findKey(int a );
};
 
#endif