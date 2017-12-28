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

// \complexity: constant (amortized time, reallocation may happen uses vector::push_back())
//
void childtable::insert(int strIndex, int inner_index){
    auto new_child = new node(strIndex, inner_index); //child to be inserted
    table.push_back(new_child);
}

// Asuming that in the future childtable will be an AVL tree or some other ordered data structure
// that supports logarithmic search
//
// \brief: Finds the position of a node in childtable.
// \brief: Returns the index of the first element in childtable who's str is equal to the parameter.
//
// \param: str The target string.
//
// \complexity: linear in the size of childtable.
int childtable::search(int str) {
    auto size = table.size();

    for(int i=0; i < size; i++){
        if(table[i]->getStr() == str){
            return i;
        }
    }
    return -1;
}

// \brief: Finds the node corresponding to the label t.
//
// \return_value: A pointer to the node.
//
// \complexity: linear in the size of childtable.
node* childtable::searchLetter(char t, vector<string> text, int h) {
    auto size = table.size();
    if(isEmpty()) return nullptr;

    for (int i = 0; i < size; i++) {
        if (text[table[i]->getStr()][table[i]->getIndex() + h - 1] == t)
            return table[i];
    }
    return nullptr;
}
