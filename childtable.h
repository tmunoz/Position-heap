#include <vector>

using namespace std;

class node;

class childtable{
public:
    vector<node*> table;
    childtable();
    int size();
    bool isEmpty();
    void print_table();
    void insert(int strIndex, int inner_index);
    node* search(char t, string* text, int h=0);
};
