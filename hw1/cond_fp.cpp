#include<stack>
#include<vector>
#include "FPNode.cpp"
using namespace std;


// FP_tree cond_fp(FP_tree fp, FPNode* list,int val, int check){
FP_tree cond_fp( FPNode* list, int check){
    if(check==0){
        FPNode* temp= list;
        FP_tree cond;
        while(temp!=NULL){
            int count = temp->counter;
            stack<int> s;
            FPNode* parent = temp->parent;
            while(parent!=NULL){
                s.push(parent.key);
                parent=parent->parent;
            }
            vector<int> v;
            while(s.size()!=0){
                v.push_back(s.top());
                s.pop();
            }
            insert(cond,v,count);
            // v.clear();
            temp = temp->next;
        }
    }
    else
    {
     // to be completed for the case of conditional fp_tree inside a conditional fp_tree
    }
}
void mineFreq(FPTree* t, std::vector<int> *v, unordered_map<int,int> *freq, std::vector<pair<int,FPNode*>> *header/*just for order*/, unordered_map<int, int> *indexFind, float s )
{
    std::vector<int> p;
    for( i:(*freq))
    {
        if(i.second>=s)
        {
            p.clear();
            p.assign(v->begin(), v->end());
            p.push_back(i.first);
            sort(p.begin(), p.end());
            for ( n :p)
            {
                cout << n << " ";
            }
            cout << "\n";
        }
    }
}