#include<stack>
#include<vector>
#include "FPNode.cpp"
using namespace std;


// FP_tree cond_fp(FP_tree fp, FPNode* list,int val, int check){
// FP_tree cond_fp( FPNode* list, int check){
FP_tree cond_fp( FPNode* list){
    // if(check==0){
        FPNode* temp= list;
        FP_tree cond;
        while(temp!=NULL)
        {
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
    // }
    // else
    // {
    //  // to be completed for the case of conditional fp_tree inside a conditional fp_tree
    // }
}
// void mineFreq(FPTree* t, std::vector<int> *vLeafs, unordered_map<int,int> *freq, std::vector<int> *prefix, std::vector<int> *ordered/*just for order*/, float s )
void mineFreq(FPTree* t, FPNode *vLeafs, std::vector<pair<int,int>> *freq, std::vector<int> *prefix, std::vector<int> *ordered/*just for order*/, float s )
{
    std::vector<int> p;
    // FPTree cfd=*t;
    FPNode *n;
    p.assign(prefix->begin(), prefix->end());

    for( int  i=freq->size()-1; i>=0;i--)
    {
        if(i.second>=s)
        {
            // printing the 
            // p.clear();
            p.push_back(i.first);//assuming the vector prefix is in decreasing order
            // sort(p.begin(), p.end());
            for ( int j=p.size(); j>=0; j--)
            {
                cout << p[j] << " ";
            }
            //call mineFreq recursively.
            n=cond_fp(vLeafs,validNodes);
            //recursive call done.
            p.pop_back();
            cout << "\n";
        }
    }
}