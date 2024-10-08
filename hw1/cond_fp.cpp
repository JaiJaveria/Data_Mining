#include<stack>
#include<vector>
#include "FPNode.h"
#include <unordered_set>
#include <algorithm>
using namespace std;

FPNode* cond_fp( FPNode* list, unordered_set<int> *notValidNodes, std::unordered_map<int,int> *freq, int a )
{

    //leafnodes list to be returned
    FPNode* iter= list;
    FPNode* temp= list;
    FPNode* ret;
    FPTree cond;
    //temp is the leaf nodes of the conditional fp tree. 
    while(temp!=NULL)
    {
        if(temp->key!=a)
        {
            temp=temp->next;
            continue;
        }
        int count;
        count=temp->counter;
        stack<int> s;
        FPNode* parent = temp->parent;
        vector<int> v;
        //go up the tree to find the sequence which has count number of occurances
        while(parent->key!=-1)
        {
                if(notValidNodes!=NULL)
                {

                    if(notValidNodes->find(parent->key)==notValidNodes->end())
                        s.push(parent->key);
                }
                else
                    s.push(parent->key);
            parent=parent->parent;
        }
        v.clear();
        //s is the reverse of the sequence. extract the sequnce to the vector v
        while(s.size()!=0){
            v.push_back(s.top());
            s.pop();
        }
        //add the sequence in vector v to the cond fp tree.
        if(v.size()>0)
            cond.insert(v,count, freq);
        temp = temp->next;
    }
    //cond will be the root of the cond fp tree. we need the list of leaf node. generate that and return.
    ret=cond.buildLeafList();
    return ret;
   }
void updateLeafN(FPNode** n, int i)
{
    //remove the nodes with key = i from the list n.
    FPNode* t=*n;
    FPNode* iter=*n;
    unordered_set<FPNode*> isPresent;
    FPNode* p=NULL;
    FPNode* temp;
    while(iter!=NULL)
    {
       
        isPresent.insert(iter);
        iter=iter->next;
    }
    while(t!=NULL)
    {
        if(t->key==i)
        {
            //this node should be deleted. remove it and add its parent.
            
            //but if the parent already exist. just delete the node
            if(isPresent.find(t->parent)!=isPresent.end() )
            {
                
            //better way(maybe): either the previous node or the next node can be the parent
                temp=t->next;
                if(p!=NULL)
                    p->next=temp;
                else
                    *n=temp;
                t->next=NULL;
                t=temp;
                continue;
            }
            else
            {
                if(t->parent->key==-1)//parent is root( null )
                {

                    if(t->next==NULL)//no next element in the leaf list
                    {
                        if(p==NULL)
                         {   
                             //the search is over.
                             //set n to root and return.
                             *n=t->parent;
                             (*n)->next=NULL;
                             return;
                         }
                         else
                         {
                            p->next=NULL;
                         }
                    }
                    //else just remove this element from the list
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
                    //if parent is not the root, add the parent to the list and remove the current node.
                    t->parent->next=t->next;
                    if(p!=NULL)
                        p->next=t->parent;
                    else
                    {
                        (*n)=t->parent;
                    }
                    temp=t->next;
                    t->next=NULL;
                    p=t->parent;
                    t=temp;
                }
            }    
        }
        else
        {
            p=t;
            t=t->next;
        }
        
    }
}

void mineFreq( FPNode *vLeafs, std::unordered_map<int,int> *freq, std::vector<int> *order , std::vector<int> *prefix, float s )
{
    std::vector<int> p;
    unordered_set<int> notValidNodes;
    FPNode *n=vLeafs;
    p.assign(prefix->begin(), prefix->end());
    
    for( int  i=order->size()-1; i>=0;i--)
    {
        if((*freq)[((*order)[i])]<s)
            notValidNodes.insert((*order)[i]);
    }
    for( int  i=order->size()-1; i>=0;i--)
    {
        if((*freq)[((*order)[i])]>=s && (*freq)[((*order)[i])]>0)
        {
            p.push_back((*order)[i]);//assuming the vector prefix is in decreasing order
            for ( int j=p.size()-1; j>0; j--)
            {
                if(to_string(p[j])<to_string(p[j-1]))
                {
                    int a=p[j-1];
                    p[j-1]=p[j];
                    p[j]=a;
                }
            }
            //print the frequent itemset
            for ( int j=0; j<p.size(); j++)
                cout << p[j] << " ";
            cout << "\n";

            if( (!(n->key==-1)) && i>0)
            {
                //call mineFreq recursively.
                FPNode *newN;
                std::vector<int> newOrder;
                newOrder.assign(order->begin(), order->begin()+ i);//debug
                unordered_map<int,int> newFreq;
                newN=cond_fp(n,&notValidNodes, &newFreq,(*order)[i]);
                mineFreq(newN, &newFreq, &newOrder, &p, s);
                updateLeafN(&n,(*order)[i]);// update the leaf nodes. the current item should be removed.
                newFreq.clear();
                //recursive call done.
            }
            p.erase(find(p.begin(), p.end(), (*order)[i]));//erase the element added
        }
        else
        {
            if(n->key!=-1 && i>0)
                updateLeafN(&n,(*order)[i]);// update the leaf nodes. the current item should be removed.

        }

    }
    FPNode* del=n;
    while(del->parent!=NULL)
        del=del->parent;
    delete del;
}
