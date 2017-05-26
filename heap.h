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
    void delete_str(int substr);
    void print(node* root);
    void GraphTree();
    void GraphTreeRecurse(node* root, ostream &out, int h = 0);
    node* getRoot();
    string* getText();
};
