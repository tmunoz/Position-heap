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
        if (text[i] == "") continue;
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

    while (temp->child->searchLetter(text[str][index + h], text, h) != nullptr) {
        temp = temp->child->searchLetter(text[str][index + h], text, h);
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
// TODO: ask if it is kinda linear?? O(K*h) = O(h) and if the complexity is ok
//
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

void heap::insert_str(string str) {
    long long int str_index;
    numberOfStrings++;
    if (fstack.isCollectionEmpty()) {
        str_index = fstack.get_index();
        str = str + "$" + to_string(str_index);
        text.push_back(str);
    } else {
        str_index = fstack.get_index();
        str = str + "$" + to_string(str_index);
        text[str_index] = str;
    }

    for (int i = 0; i < str.size() - 1; i++) {
        if (text[str_index][i] == '$') break;
        insert(str_index, i + 1);
    }

    setMaxReaches();
}

// Returns the node's parent and his position on the table
std::pair<node*, int> heap::searchStr(node* root, int str) {
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
            auto *childToPromote = new node(INT_MAX, INT_MAX);
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

    text[substr - 1] = "";
    fstack.add_deleted(substr-1);


    setMaxReaches();

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
    std::vector<node *> path, sol;
    int h = 0;
    while (pattern.size() > h && (temp = temp->child->searchLetter(pattern[h], text, h)) != nullptr) {
        path.push_back(temp);
        h++;
    }
    if (pattern.size() == h) {
        queue<node *> q;
        unordered_map<node *, node *> subtreeKeys;
        q.push(temp);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            sol.push_back(u);
            subtreeKeys.insert(make_pair(u, u));
            for (auto &elem : u->child->table) {
                q.push(elem);
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
    while (true) {
        auxSol.clear();
        for (auto &elem : path) {
            if (maxReach.at(make_pair(elem->getStr(), elem->getIndex())) == temp)
                auxSol.push_back(elem);
        }

        int h2 = 0;
        temp = root;
        path.clear();
        while ((pattern.size() > h + h2) && (temp = temp->child->searchLetter(pattern[h + h2], text, h2)) != nullptr) {
            path.push_back(temp);
            h2++;
        }

        if (h2 == pattern.size() - h) {
            queue<node *> q;
            unordered_map<node *, node *> subtreeKeys;
            q.push(temp);
            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                subtreeKeys.insert(make_pair(u, u));
                for (auto &elem : u->child->table) {
                    q.push(elem);
                }
            }

            for (auto &elem : auxSol) { // if they are in the same string... Searching for the nodes in auxSol (list) who have their mrp pointing to the subtree of v'
                auto p = new node(elem->getStr(), elem->getIndex() + h);
                if (subtreeKeys.find(maxReach[make_pair(elem->getStr(), elem->getIndex() + h)]) !=
                    subtreeKeys.end() || find(path.begin(), path.end(), p) != path.end()) { //if getindex()+h is on the path from root to v' with a mrp into the subtree of v'
                    sol.push_back(elem);
                }
            }

            return sol;
        }

        if (h2 + h != pattern.size()) h = h2;
        else {
            return {nullptr};
        }
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

    for (int i = 0; i < root->child->size(); i++) {
        int child_str = root->child->table[i]->getStr();
        int child_index = root->child->table[i]->getIndex();
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

    for (int i = 0; i < root->child->size(); i++) {
        heap::GraphTreeRecurse(root->child->table[i], out, h + 1);
    }

}

node* heap::getRoot() {
    return root;
}

vector<string> heap::getText() {
    return text;
}
