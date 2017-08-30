#include <vector>
#include <iostream>
#include <utility>
#include "childtable.h"
#include "node.h"

unsigned long childtable::size() {
    return table.size();
}

bool childtable::isEmpty(){
    return table.empty();
}

childtable::childtable(){}

void childtable::print_table() {
    for(int i=0;i < table.size();i++){
        cout<<"("<<table[i]->getStr()+1<<", "<<table[i]->getIndex()<<") ";
    }
}

void childtable::insert(int strIndex, int inner_index){
    node* new_child = new node(strIndex, inner_index); //child to be inserted
    table.push_back(new_child);
}

// Asuming that in the future childtable will be an AVL tree or some other ordered data structure
// that supports logarithmic search
int childtable::search(int str) {
    unsigned long size = table.size();

    for(int i=0; i < size; i++){
        if(table[i]->getStr() == str){
            return i;
        }
    }
    return -1;
}

node* childtable::searchLetter(char t, string* text, int h) {
    unsigned long size = table.size();
    for (int i = 0; i < size; i++) {
        if (text[table[i]->getStr()][table[i]->getIndex() + h - 1] == t)
            return table[i];
    }
    return nullptr;
}
