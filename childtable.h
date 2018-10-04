#include <unordered_map>
#include <vector>

using namespace std;

class node;

class childtable{
public:
    unordered_map<char, node*> table;
    childtable();
    unsigned long size();
    bool isEmpty();
    void print_table();
    void insert(int strIndex, int inner_index, char label);
    node* searchLetter(char t);
    int search(int str);
};
