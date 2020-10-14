#include<stack>
#include<vector>
#include "FPNode.cpp"
using namespace std;


// FP_tree cond_fp(FP_tree fp, FPNode* list,int val, int check){
// FP_tree cond_fp( FPNode* list, int check){
// FP_tree cond_fp( FPNode* list){
FPNode* cond_fp( FPNode* list, unordered_set<int> *notValidNodes, std::unordered_map<int,int> *freq )
{
    // if(check==0){

    //leafnodes list to be returned
        FPNode* temp= list;
        FPNode* ret;
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
        ret=cond.buildLeafList();
        return ret;
    // }
    // else
    // {
    //  // to be completed for the case of conditional fp_tree inside a conditional fp_tree
    // }
}
void updateLeafN(FPNode** n, int i)
{
    FPNode* t=*n;
    FPNode* p=NULL;
    FPNode* temp;
    while(t!=NULL)
    {
        if(t.key==i)
        {
            if(t->parent->key==-1)//parent is root( null )
            {
                if(t->next==NULL)
                {
                    //the search is over.
                    //set n to root and return.
                    *n=t->parent;
                    return;
                }
                if(p!=NULL)
                    p->next=t->next;
                else
                    *n=t->next;
                temp=t->next;
                t->next=NULL;
                t=temp;

            }
            else
            {
                //if parent already there in list, it will definately be either just next to the node or just prev in the list.
                //if it is just next then no issues. if prev then we do not want a self loop.
                if(p==t->parent)
                {
                    //do not need a self loop
                    p->next=t->next;
                    t->next=NULL;
                    t=p->next;
                    continue;
                }
                t->parent->next=t->next;
                if(p!=NULL)
                    p->next=t->parent;
                else
                {
                    (*n)=t->parent;
                    // (*n)->next=NULL;

                }
                temp=t->next;
                t->next=NULL;
                p=t->parent;
                t=temp;
            }
            

        }
        else
        {
            p=t;
            t=t->next;
        }
    }
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
            //sorting req.
            for ( int j=p.size(); j>=0; j--)
                cout << p[j] << " ";
            //call mineFreq recursively.
            FPNode *newN;
            // std::vector<pair<int,int>> newfreq, std::vector<int> newPre;
            std::vector<pair<int,int>> newOrder;
            newOrder.assign(order.begin(), order.find(i)-1);//debug
            unordered_map<pair<int,int>> newFreq;
            newN=cond_fp(n,&notValidNodes, &newFreq);
            // delete n;
            // n=newN;
            mineFreq(newN, &newFreq, &p, s);
            delete *newN;
            updateLeafN(&n,i.first);// update the leaf nodes. the current item should be removed.
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