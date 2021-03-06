/**************************************************/
// Dynamic Position Heap by Thomas Muñoz, thomas.munoz@mail.udp.cl
// Based on Ross McConell position-heap implementation
// http://www.cs.colostate.edu/PositionHeaps/
/**************************************************/
#include <cstdio>
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include "heap.h"
#include "node.h"
#include "childtable.h"

heap::heap(){
    text.clear();
    root = new node(0,0);
    numberOfStrings = 0;
}

/*********************************************************/
// TODO: Add time bounds of everything
// Goes through the text calling insert for each character
//
/*********************************************************/

// \brief: Set a maximal-reach pointer for every node in the heap.
//
// \complexity: O(n*m*[h*k]) where n is the number of strings in the text and m is the size of the strings.
//  h and k are explained in mrpAuxiliar
//
// \about: Maximal-Reach pointers (MRPs) as our structure is dynamic we have to
// update the MRPs every time that a new string is inserted.
//
void heap::setMaxReaches() {
    maxReach.clear();
    for (int i = 0; i < text.size(); i++) { // i = string & j = index
        if (text[i].empty()) continue;
        for (int j = 0; j < text[i].size() - 1; j++) {
            mrpAuxiliar(i, j);
        }
    }
}

// \brief: Set the maximal-reach pointer of the node(str, index)
// \brief: For each string str[1..n] and for index index[1..n] start at the root and
//      descend according to s[index+h..n] until the deepest node v whose path label is a prefix of str is reached,
//      will pass the node (str, index), finally set a mrp from (str, index) to the node v.
//
//  * Each mrp will be stored in the unordered_map maxReach
//
// \param: The str and index of the node whose mrp is going to be set.
//
// \complexity: O(h*k) where h is the height of v and k is the number of different labels in the text.
//  TODO: ask if it is kinda linear?? O(K*h) = O(h) and if the complexity is ok
//
void heap::mrpAuxiliar(int str, int index) { // estan como str, index+1
    node *temp = root;

    int h = 0;
    bool node_reached = false;
    if (root->child->isEmpty()) return;

    while (temp->child->searchLetter(text[str][index + h]) != nullptr) {
        temp = temp->child->searchLetter(text[str][index + h]);
        if (temp->getStr() == str && temp->getIndex() - 1 == index) node_reached = true;
        h++;
        if (index + h > text[str].size()) break;
    }
    if (!node_reached) return;
    maxReach[make_pair(str, index + 1)] = temp;
}

// \brief: Insert a new node(string, index) in the heap. Follow text[string] until it hits a leaf or
//  label text[string][index+h] is not in the childtable of a node.
//
// \complexity: O(h*k) where h is the height of the last node reached and k is the number of different labels in the text.
// TODO: check complexity
//
void heap::insert(int substr, int index) {
    node *temp = root;
    if (root->child->isEmpty()) { // checks if root childtable is empty
        root->child->insert(substr, index, text[substr][index]);
    } else if (temp->child->searchLetter(text[substr][index])
               == nullptr) { // checks if root's childtable has the char text[substr][index-1]
        temp->child->insert(substr, index, text[substr][index]); // executes childtable search
    } else {
        temp = temp->child->searchLetter(text[substr][index]);
        int new_index = index + 1;
        while (temp->child->searchLetter(text[substr][new_index]) != nullptr) {
            temp = temp->child->searchLetter(text[substr][new_index]);
            new_index++;
            if (new_index > text[substr].size()) return;
        }
        temp->child->insert(substr, index, text[substr][index+1]);
    }
}

long long heap::insert_str(string str) {
    long long int str_index;
    numberOfStrings++;
    if (fstack.isCollectionEmpty()) {
        str_index = fstack.get_index();
        str = str + "$" + to_string(str_index+1);
        text.push_back(str);
    } else {
        str_index = fstack.get_index();
        str = str + "$" + to_string(str_index+1);
        text[str_index] = str;
    }

    for (int i = 0; i < str.size() - 1; i++) {
        if (text[str_index][i] == '$') {
            //insert(str_index, i-1);
            break;
        }
        insert(str_index, i);
    }

    setMaxReaches();
    return str_index+1;
}

// Returns the node's parent and his key on the table
pair<node*, int> heap::searchStrNodes(node* root, int str, int i) {
    if (root->child->isEmpty()) return {nullptr, 0};

    node* found = root->child->searchLetter(text[str-1][i]);
    if(!found) return {nullptr, 0};
    else if (found->getStr() == str-1 ) return {root, i};

    else {
        return searchStrNodes(found, str, i+1);
    }

}

void heap::delete_str(int str) {
    pair<node*, int> parent = heap::searchStrNodes(root, str);
    while(parent.first){
        node* nodeToDelete = parent.first->child->table[text[str-1][parent.second]];
        if(nodeToDelete->child->isEmpty()){
            parent.first->child->table.erase(text[str-1][parent.second]);
            delete nodeToDelete;

        } else{
            node *aux = nodeToDelete;
            auto *childToPromote = new node(999, 999); //TODO: check
            char keyToPromote = ' ';
            for (auto &elem : aux->child->table) {
                if (elem.second->getStr() < childToPromote->getStr()) {
                    childToPromote = elem.second;
                    keyToPromote = elem.first;
                } else if (elem.second->getStr() == childToPromote->getStr() &&
                        elem.second->getIndex() < childToPromote->getIndex()) {
                    childToPromote = elem.second;
                    keyToPromote = elem.first;
                }
            }
            aux->child->table.erase(keyToPromote);
            childToPromote->child->table.insert(aux->child->table.begin(), aux->child->table.end());
            parent.first->child->table.erase(text[str-1][parent.second]);
            parent.first->child->table.insert({text[str-1][parent.second], childToPromote});
            delete nodeToDelete;
        }
        parent = heap::searchStrNodes(root, str, parent.second+1);
    }
    text[str - 1] = "";
    fstack.add_deleted(str-1);

    setMaxReaches();
}

bool find(const vector<node*> list, node* val){
    for(auto &a : list){
        if (a->getStr() == val->getStr() && a->getIndex() == val->getIndex()) return true;
    }
    return false;
}

// \brief: Search for a pattern in the heap, returns a vector with the nodes (str, index) denoting the position
//      of every ocurrence of the pattern on the text.
//  p = length of the pattern
//  k = number of different letters on the text (could be reduced using a map because it'll improve searchLetter function)
//  h = number of nodes on the path from the root to the deepest node reachable on the heap following the pattern
//
// TODO: get the complexity
//
vector<node*> heap::search(string pattern) {
    node *temp = root;
    std::vector<node *> path, sol, filteredList;
    int h = 0;
    while (pattern.size() > h && (temp->child->searchLetter(pattern[h]) != nullptr)) {
        temp = temp->child->searchLetter(pattern[h]);
        path.push_back(temp);
        h++;
    }
    if (pattern.size() == h) {
        queue<node*> q;
        unordered_map<node *, node *> subtreeKeys;
        q.push(temp);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            sol.push_back(u);
            subtreeKeys.insert(make_pair(u, u));
            for (auto &elem : u->child->table) {
                q.push(elem.second);
            }
        }

        path.pop_back();
        for (auto &elem : path) {
            if (subtreeKeys.find(maxReach[make_pair(elem->getStr(), elem->getIndex())]) != subtreeKeys.end()) {
                sol.push_back(elem);
            }
        }
        return sol;
    }

    vector<node *> auxSol;
    for (auto &elem : path) {
        if (maxReach.at(make_pair(elem->getStr(), elem->getIndex())) == temp)
            auxSol.push_back(elem);
    }

    while(true) {
        int h2 = 0;
        temp = root;
        filteredList.clear();

        path.clear();
        sol.clear();
        while ((pattern.size() > h + h2) && (temp->child->searchLetter(pattern[h + h2]) != nullptr)) {
            temp = temp->child->searchLetter(pattern[h + h2]);
            path.push_back(temp);
            h2++;
        }

        if (h2 == pattern.size() - h) {
            queue<node *> q;
            vector<node *> subtreeKeys; // TODO: change data structure if time is too low
            q.push(temp);
            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                subtreeKeys.push_back(u);
                for (auto &elem : u->child->table) {
                    q.push(elem.second);
                }
            }

            for (auto &elem : auxSol) { // if they are in the same string... Searching for the nodes in auxSol (list) who have their mrp pointing to the subtree of v'
                auto p = new node(elem->getStr(), elem->getIndex() + h);
                if (find(subtreeKeys, p) ||
                        (find(subtreeKeys, maxReach[make_pair(p->getStr(), p->getIndex())]) &&
                         find(path, p))) { //if getindex()+h is on the path from root to v' with a mrp into the subtree of v'
                    sol.push_back(elem);
                }
            }

            return sol;
        }

        for (auto &elem : auxSol) {
            auto p = new node(elem->getStr(), elem->getIndex() + h);
            if ((maxReach[make_pair(p->getStr(), p->getIndex())] == temp) && find(path, p))
                filteredList.push_back(elem);
        }
        auxSol=filteredList;
        if (h2 + h < pattern.size()) h += h2;
        else {
            return {nullptr};
        }

    }

}

void heap::print(node* root) {
    if (root->child->isEmpty()) {
        return;
    }
    for(auto node : root->child->table){
        heap::print(node.second);
    }
    root->child->print_table();
}

void heap::GraphTree() {
    std::ofstream out("tree.txt");
    out << "digraph G{\n";
    GraphTreeRecurse(root, out);
    for (auto &elem : maxReach) {
        out << "\"" << elem.first.first + 1 << ", " << elem.first.second << "\" -> \""
            << elem.second->getStr() + 1 << ", " << elem.second->getIndex()
            << "\" [color = \"0.002 0.999 0.999\"]\n";
    }
    out << "}";
    out.close();
}

void heap::GraphTreeRecurse(node* root, ostream &out, int h) {
    if (root->child->isEmpty()) return;
    for ( auto child : root->child->table){
        int child_str = child.second->getStr();
        int child_index = child.second->getIndex();
        int parent_index;
        int parent_str;


        if (root == heap::root) {
            parent_str = -1;
            parent_index = 0;
        } else {
            parent_str = root->getStr();
            parent_index = root->getIndex();
        }
        // Writing on tree.txt
        out << "\"" << parent_str + 1 << ", " << parent_index << "\" -> \""
            << child_str + 1 << ", " << child_index << "\" [label = \" "
            << text[child_str][child_index - 1 + h] << "\"]\n";
    }

    for (auto child : root->child->table) {
        heap::GraphTreeRecurse(child.second, out, h + 1);
    }
}

node* heap::getRoot() {
    return root;
}

vector<string> heap::getText() {
    return text;
}

heap::~heap(){
    delete root;
}
