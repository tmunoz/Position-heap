#include <vector>

using namespace std;

class node;

class childtable{
public:
    vector<node*> table;
    childtable();
    unsigned long size();
    bool isEmpty();
    void print_table();
    void insert(int strIndex, int inner_index);
    node* searchLetter(char t, string* text, int h=0);
    int search(int str);
};
