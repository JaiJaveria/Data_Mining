#include "FPNode.cpp"
#include <iostream>
using namespace std;




int main(){
    FPNode *a = new FPNode(1);
    vector<int> v = {1,3,9,8,8};
    vector<int> v2 = {1,2,5,4};
    a->insert(v,1,0);
    a->insert(v2,1,0);
    FPNode *p = a;
    for(int i=0;i<5;i++){
    if(a->children.find(v[i])!=a->children.end()){
       
        a = (a->children[v[i]]); 
        cout<<a->key<<" "<<a->counter<<endl;
        
    }
    }
    for(int i=0;i<4;i++){
    if(p->children.find(v2[i])!=p->children.end()){
       p  = (p->children[v2[i]]); 
        
        cout<<p->key<<" "<<p->counter<<endl;
        
    }
    }
}