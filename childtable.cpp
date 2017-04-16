#include <vector>
#include <iostream>
#include "childtable.h"
#include "node.h"

int childtable::size() {
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

node* childtable::search(char t, string* text, int h) {
    for(int i=0; i < table.size(); i++) {
        if(text[table[i]->getStr()][table[i]->getIndex()+h-1] == t)
            return table[i];
    }
    return nullptr;
}
