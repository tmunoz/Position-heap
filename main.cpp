#include <iostream>
#include "heap.h"
#include "node.h"
#include "childtable.h"
#include <unordered_map>

int main(){
    string* a;
    int n=4;
    a = new string[n];
    //alabaralaalabadaalabarda
    a[0]="abaa$";
    a[1]="babb$";
    a[2]="abba$";
    a[3]="b$";
    heap *h;
    h = new heap(a,n);
    h->build();
    h->print(h->getRoot());
    h->GraphTree();
    auto res = h->search("babb");
    cout<<endl;
    for(auto &elem : res) cout<<elem->getStr()+1<<", "<<elem->getIndex()<<endl;
    /*
    std::cout<<"\n";
    h->delete_str(1);
    h->print(h->getRoot());
    h->GraphTree();
     */
    delete h;
}