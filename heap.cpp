/**************************************************/
// Based on Ross McConell position-heap implementation
// http://www.cs.colostate.edu/PositionHeaps/
/**************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include "heap.h"
#include "node.h"
#include "childtable.h"

heap::heap(string* txt, int nOStr){
    root = new node(0,0);
    text = new string[nOStr];
    for(int i=0; i < nOStr; i++){
        text[i]=txt[i];
    }
    numberOfStrings = nOStr;
}

/*********************************************************/
//
// Goes through the text calling insert for each character
//
/*********************************************************/
void heap::build() {
    for (int i = 0; i < numberOfStrings; i++) { // i = string index & j = index
        for(int j=0; j<text[i].size()-1; j++){
            insert(i,j+1);
        }
    }
}

void heap::insert(int substr, int index) {
    node *temp = root;
    if (root->child->isEmpty()) { // checks if root childtable is empty
        root->child->insert(substr, index);
    }
    else if (temp->child->search(text[substr][index-1], text) == nullptr) { // checks if root's childtable has the char text[substr][index-1]
        temp->child->insert(substr, index); // executes childtable search
    }
    else {
        temp = temp->child->search(text[substr][index-1], text); // h=0
        int new_index=index+1; // is declared here for better understanding
        while (temp->child->search(text[substr][new_index-1], text, new_index-index) != nullptr) {
            temp = temp->child->search(text[substr][new_index-1], text, new_index-index);
            new_index++;
            if(new_index>text[substr].size()) return;
        }
        temp->child->insert(substr, index);
    }
}

void heap::delete_str(int substr){

}

void heap::print(node* root) {
    if(root->child->isEmpty()){
        return;
    }
    for(int i=0;i < root->child->size();i++){
        heap::print(root->child->table[i]);
    }
    root->child->print_table();
}

node* heap::getRoot() {
    return root;
}
