#include<stack>
#include<vector>
// #include "FPNode.cpp"
#include "FPNode.h"
#include <unordered_set>
#include <algorithm>
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
        FPTree cond;
        while(temp!=NULL)
        {
            // cout << "23C"<<endl;

            int count = temp->counter;
            stack<int> s;
            FPNode* parent = temp->parent;
            vector<int> v;
            
            while(parent->key!=-1)
            // while(parent!=NULL)
            {
                if(notValidNodes!=NULL)
                {

                    if(notValidNodes->find(parent->key)==notValidNodes->end())
                        s.push(parent->key);
                }
                else
                    s.push(parent->key);

                parent=parent->parent;
                // cout << "29C\n";

            }
            // cout << "42--"<<endl;
            // cout << "35C--" << s.size();
            // cout << endl;
            
            v.clear();
            while(s.size()!=0){
                v.push_back(s.top());
                s.pop();
            }

            // cout << "38C"<<endl;
            // for(auto i: v)
            // {
            //     cout << i << " ";

            // }
            // cout <<endl;

            if(v.size()>0)
                cond.insert(v,count, freq);
            // cout << "64C"<<endl;

            temp = temp->next;
        }
        // cout << "50C Cond FP Tree"<<endl;
        // cond.print();
        // cout << "42C\n"<<endl;
        
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
    FPNode* iter=*n;
    // while(iter!=NULL)
    // {
    //     cout <<iter->key<<" ";
    //     iter=iter->next;
    // }
    FPNode* p=NULL;
    FPNode* temp;
    // cout<<"87C"<<endl;
    // cout<<"87"<<endl;
    // cout<<(*n)->key<<endl;
    // cout<<i<<endl;
    while(t!=NULL)
    {
        // cout << t->key<<endl;
        if(t->key==i)
        {
            // cout<<"96C"<<endl;

            if(t->parent->key==-1)//parent is root( null )
            {
                // cout<<"100C"<<endl;

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
            // cout<<"120C"<<endl;

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
                // if(t->next!=NULL)
                // {

                // }
                if(t->next==t->parent)
                {
                    if(p!=NULL)
                        p->next=t->parent;
                    else
                        (*n)=t->parent;
                    t->next=NULL;
                    t=t->parent;
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
        if((*freq)[((*order)[i])]<s)
            notValidNodes.insert((*order)[i]);
    }
    for( int  i=order->size()-1; i>=0;i--)
    {
        // cout << "163C-"<<i<<endl;
        // cout << "193C-"<<(*order)[i]<<endl;
        if((*freq)[((*order)[i])]>=s && (*freq)[((*order)[i])]>0)
        {
            // p.clear();
            // p.assign(prefix->begin(), prefix->end());
            p.push_back((*order)[i]);//assuming the vector prefix is in decreasing order
            //sorting req.
            // sort(p.begin(), p.end());

            for ( int j=p.size()-1; j>0; j--)
            {
                if(p[j]<p[j-1])
                // if(intToAscii(p[j])<intToAscii(p[j-1]))
                {
                    int a=p[j-1];
                    p[j-1]=p[j];
                    p[j]=a;
                }
            }
            // for ( int j=p.size()-1; j>=0; j--)
            for ( int j=0; j<p.size(); j++)
                cout << p[j] << " ";
            cout << "\n";
            if(n->key!=-1 && i>0)
            {
            //call mineFreq recursively.
                FPNode *newN;
                // std::vector<pair<int,int>> newfreq, std::vector<int> newPre;
                std::vector<int> newOrder;
                // newOrder.assign(order->begin(), (find(order->begin(), order->end(),i))-1);//debug
                // cout << "221--i-"<<i<<endl;
                newOrder.assign(order->begin(), order->begin()+ i);//debug
                // newOrder.assign(order->begin(), order->begin()+ i-1);//debug
                // cout<<"220C"<<endl;
                // cout<<n->key<<endl;
                unordered_map<int,int> newFreq;
                newN=cond_fp(n,&notValidNodes, &newFreq);
                // cout<<"186C"<<endl;
                // newN->printT();
                // cout << endl;
                mineFreq(newN, &newFreq, &newOrder, &p, s);
                // cout<< order->size()<<endl;
                // cout<< "199C"<<endl;
                delete newN;
                updateLeafN(&n,(*order)[i]);// update the leaf nodes. the current item should be removed.
                // cout<< "202C"<<endl;
                newFreq.clear();
                // newPre.clear();
                //recursive call done.
            }
            p.erase(find(p.begin(), p.end(), (*order)[i]));//erase the element added
        }
        // cout << "207N"<<endl;

    }
    // notValidNodes.clear();
    // notValidNodes.shrink_to_fit();
    // delete n;
    // p.clear();
    // p.shrink_to_fit();
}