#include<stack>
#include<vector>
#include "FPNode.cpp"
using namespace std;


// FP_tree cond_fp(FP_tree fp, FPNode* list,int val, int check){
// FP_tree cond_fp( FPNode* list, int check){
// FP_tree cond_fp( FPNode* list){
FP_tree cond_fp( FPNode* list, unordered_set<int> *notValidNodes, std::vector<pair<int,int>> *freq ){
    // if(check==0){

    //leafnodes list to be returned
        FPNode* temp= list;
        FP_tree cond;
        while(temp!=NULL)
        {
            int count = temp->counter;
            stack<int> s;
            FPNode* parent = temp->parent;
            while(parent!=NULL)
            {
                if(notValidNodes.find(parent.key)==notValidNodes.end())
                    s.push(parent.key);
                parent=parent->parent;
            }
            vector<int> v;
            while(s.size()!=0){
                v.push_back(s.top());
                s.pop();
            }
            insert(cond,v,count, freq);
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

void mineFreq( FPNode *vLeafs, std::unordered_map<int,int> *freq, std::vector<int> *order , std::vector<int> *prefix, float s )
{
    std::vector<int> p;
    // FPTree cfd=*t;
    unordered_set<int> notValidNodes;
    FPNode *n=vLeafs;
    p.assign(prefix->begin(), prefix->end());
    //finding all nodes with less frequency
    for( int  i=order->size()-1; i>=0;i--)
    {
        if(i.second<s)
            notValidNodes.insert(i.first);
    }
    for( int  i=order->size()-1; i>=0;i--)
    {
        if(i.second>=s)
        {
            p.push_back(i.first);//assuming the vector prefix is in decreasing order
            for ( int j=p.size(); j>=0; j--)
            {
                cout << p[j] << " ";
            }
            //call mineFreq recursively.
            FPNode *newN;
            // std::vector<pair<int,int>> newfreq, std::vector<int> newPre;
            std::vector<pair<int,int>> newOrder;
            newOrder.assign(order.begin(), order.find(i)-1);//debug
            unordered_map<pair<int,int>> newFreq;
            newN=cond_fp(n,&notValidNodes, &newfreq);
            delete n;
            n=newN;
            mineFreq(n, &newF, &p, s);
            // delete *n;
            newfreq.clear();
            // newPre.clear();
            //recursive call done.
            p.pop_back();
            cout << "\n";
        }
    }
    // notValidNodes.clear();
    // notValidNodes.shrink_to_fit();
    delete n;
    // p.clear();
    // p.shrink_to_fit();
}