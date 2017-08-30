#include <iostream>
#include "heap.h"
#include "node.h"
#include "childtable.h"

int main(){
    string* a;
    int n=4;
    a = new string[n];
    //alabaralaalabadaalabarda
    a[0]="abaa";
    a[1]="babb";
    a[2]="abba";
    a[3]="b$";
    heap *h;
    h = new heap(a,n);
    h->build();
    h->print(h->getRoot());
    h->GraphTree();
    /*
    std::cout<<"\n";
    h->delete_str(1);
    h->print(h->getRoot());
    h->GraphTree();
     */
    delete h;
}