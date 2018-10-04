#include <unordered_map>
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

void childtable::print_table() { // check for new way to do this in a map instead of vector
    for(auto elem : table) {
        cout << "(" << elem.second->getStr() + 1 << ", " << elem.second->getIndex() << ") ";
    }
}

// \complexity: constant, uses std::unordered_map insert.
//
void childtable::insert(int strIndex, int inner_index, char label){
    auto new_child = new node(strIndex, inner_index); //child to be inserted
    table.insert({label, new_child});
}

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
node* childtable::searchLetter(char t) {
    if(isEmpty()) return nullptr;
    auto founded = table.find(t);
    if(founded != table.end()) return founded->second;
    else return nullptr;

}
