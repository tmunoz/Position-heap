/**************************************************/
// Based on Ross McConell position-heap implementation
// http://www.cs.colostate.edu/PositionHeaps/
/**************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
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
        for (int j = 0; j < text[i].size() - 1; j++) {
            insert(i, j + 1);
        }
    }
}

void heap::insert(int substr, int index) {
    node *temp = root;
    if (root->child->isEmpty()) { // checks if root childtable is empty
        root->child->insert(substr, index);
    } else if (temp->child->search(text[substr][index - 1], text) ==
               nullptr) { // checks if root's childtable has the char text[substr][index-1]
        temp->child->insert(substr, index); // executes childtable search
    } else {
        temp = temp->child->search(text[substr][index - 1], text); // not sending h, because h = 0
        int new_index = index + 1; // is declared here for better understanding
        while (temp->child->search(text[substr][new_index - 1], text, new_index - index) != nullptr) {
            temp = temp->child->search(text[substr][new_index - 1], text, new_index - index);
            new_index++;
            if (new_index > text[substr].size()) return;
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

void heap::GraphTree() {
    std::ofstream out("tree.txt");
    out<<"digraph G{\n";
    GraphTreeRecurse(root, out);
    out<<"}";
    out.close();
}

void heap::GraphTreeRecurse(node* root, ostream &out, int h) {
    if (root->child->isEmpty()) return;

    for (int i = 0; i < root->child->size(); i++) {
        int parent_str;
        int parent_index;
        int child_str = root->child->table[i]->getStr();
        int child_index = root->child->table[i]->getIndex();

        if (root == heap::root){
            parent_str=0;
            parent_index=0;
        } else {
            parent_str = root->getStr()+1;
            parent_index = root->getIndex();
        }
        // Writing on tree.txt
        out << "\"" << parent_str << ", " << parent_index << "\" -> \""
            << child_str + 1 << ", " << child_index << "\" [label = \" "
            << text[child_str][child_index - 1 + h] << "\"]\n";
    }

    for (int i = 0; i < root->child->size(); i++) {
        heap::GraphTreeRecurse(root->child->table[i], out, h+1);
    }

}

node* heap::getRoot() {
    return root;
}

string* heap::getText() {
    return text;
}