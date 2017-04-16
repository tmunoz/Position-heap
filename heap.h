#include <vector>

class node;
class childtable;

using namespace std;

class heap{
    node* root;
    string* text;
    int numberOfStrings;
public:
    heap(string* txt, int nOStr);
    void build();
    void insert(int substr, int index);
    void print(node* root);
    node* getRoot();
};
