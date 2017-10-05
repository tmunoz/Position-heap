/**************************************************/
// Based on Ross McConell position-heap implementation
// http://www.cs.colostate.edu/PositionHeaps/
/**************************************************/
#include <cstdio>
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
// TODO: Add time bounds of everything
// Goes through the text calling insert for each character
//
/*********************************************************/
void heap::build() {
    for (int i = 0; i < numberOfStrings; i++) { // i = string & j = index
        for (int j = 0; j < text[i].size() - 1; j++) {
            insert(i, j + 1);
        }
    }
    setMaxReaches();
}

void heap::setMaxReaches() {
    for (int i = 0; i < numberOfStrings; i++) { // i = string & j = index
        for (int j = 0; j < text[i].size() - 1; j++) {
            mrpAuxiliar(i, j);
        }
    }
}

void heap::mrpAuxiliar(int str, int index) { // estan como str, index+1
    node *temp = root;

    int h = 0;
    bool node_reached = false;
    if (root->child->isEmpty()) return;

    while (temp->child->searchLetter(text[str][index + h], text, h) != nullptr) {
        temp = temp->child->searchLetter(text[str][index + h], text, h);
        if (temp->getStr() == str && temp->getIndex() - 1 == index) node_reached = true;
        h++;
        if (index + h > text[str].size()) break;
    }
    if (!node_reached) return;
    maxReach[std::pair<int, int>(str, index + 1)] = temp;
}

// TODO: bla bla bla about insert...
// About Maximal-Reach pointers (MRPs), because our structure is dynamic we have to
// update the MRPs every time that a new string is inserted.
void heap::insert(int substr, int index) {
    node *temp = root;
    if (root->child->isEmpty()) { // checks if root childtable is empty
        root->child->insert(substr, index);
    } else if (temp->child->searchLetter(text[substr][index - 1], text)
               == nullptr) { // checks if root's childtable has the char text[substr][index-1]
        temp->child->insert(substr, index); // executes childtable search
    } else {
        temp = temp->child->searchLetter(text[substr][index - 1], text); // not sending h, because h = 0
        int new_index = index + 1;  // h+=1
        while (temp->child->searchLetter(text[substr][new_index - 1], text, new_index - index) != nullptr) {
            temp = temp->child->searchLetter(text[substr][new_index - 1], text, new_index - index);
            new_index++;
            if (new_index > text[substr].size()) return;
        }
        temp->child->insert(substr, index);
    }
}

// Returns the node's parent and his position on the table
std::pair<node*, int> heap::searchStr(node* root, int str) { // TODO: rename to Search Parent
    if (root->child->isEmpty()) return {nullptr, 0};

    int found = root->child->search(str);
    if (found >= 0) return std::make_pair(root, found);

    for (int i = 0; i < root->child->size(); i++) {
        return heap::searchStr(root->child->table[i], str);
    }
}

void heap::delete_str(int substr) {
    std::pair<node *, int> parent = heap::searchStr(root, substr - 1); //substr-1 because strings are stored from 0 to n
    while (parent.first) {
        node *nodeToDelete = parent.first->child->table[parent.second];
        if (nodeToDelete->child->isEmpty()) {
            parent.first->child->table.erase(parent.first->child->table.begin() + parent.second);
            delete nodeToDelete;

        } else {
            node *aux = nodeToDelete;
            auto *childToPromote = new node(999, 999); // TODO: set as the first element on aux->child->table
            int posOfPromotingChild = 0, i = 0;
            for (auto &elem : aux->child->table) {
                if (elem->getStr() < childToPromote->getStr()) {
                    childToPromote = elem;
                    posOfPromotingChild = i;
                } else if (elem->getStr() == childToPromote->getStr() &&
                           elem->getIndex() < childToPromote->getIndex()) {
                    childToPromote = elem;
                    posOfPromotingChild = i;
                }
                ++i;
            }
            aux->child->table.erase(aux->child->table.begin() + posOfPromotingChild);
            childToPromote->child->table.insert(childToPromote->child->table.end(),
                                                aux->child->table.begin(), aux->child->table.end());
            parent.first->child->table[parent.second] = childToPromote;
            delete nodeToDelete;
        }
        parent = heap::searchStr(root, substr - 1);
    }

    string *new_text = new string[numberOfStrings]; //TODO: erase the string that I'm deleting instead of leaving it there
    for (int i = 0; i < numberOfStrings + 1; i++) {
        if (i == substr - 1) text[i] = "";
        else new_text[i] = text[i];
    }

    text = new string[numberOfStrings];
    for (int i = 0; i < numberOfStrings; i++) {
        text[i] = new_text[i];
    }
}

void heap::print(node* root) {
    if (root->child->isEmpty()) {
        return;
    }
    for (int i = 0; i < root->child->size(); i++) {
        heap::print(root->child->table[i]);
    }
    root->child->print_table();
}

void heap::GraphTree() {
    std::ofstream out("tree.txt");
    out << "digraph G{\n";
    GraphTreeRecurse(root, out);
    out << "}";
    out.close();
}

void heap::GraphTreeRecurse(node* root, ostream &out, int h) {
    if (root->child->isEmpty()) return;

    for (int i = 0; i < root->child->size(); i++) {
        int child_str = root->child->table[i]->getStr();
        int child_index = root->child->table[i]->getIndex();
        int parent_index;
        int parent_str;


        if (root == heap::root) {
            parent_str = 0;
            parent_index = 0;
        } else {
            parent_str = root->getStr() + 1;
            parent_index = root->getIndex();
        }
        // Writing on tree.txt
        out << "\"" << parent_str << ", " << parent_index << "\" -> \""
            << child_str + 1 << ", " << child_index << "\" [label = \" "
            << text[child_str][child_index - 1 + h] << "\"]\n";
    }

    for (int i = 0; i < root->child->size(); i++) {
        heap::GraphTreeRecurse(root->child->table[i], out, h + 1);
    }

}

node* heap::getRoot() {
    return root;
}

string* heap::getText() {
    return text;
}
