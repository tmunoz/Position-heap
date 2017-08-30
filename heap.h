#include <vector>
#include <utility>
#include <unordered_map>

class node;
class childtable;

using namespace std;

class heap{
    std::unordered_map<std::pair<int, int>, node*> maxReach; // An unordered_map is used because it's space optimal
    // and has average constant time complexity
    int numberOfStrings;
    node* root;
    string* text;
public:
    heap(string* txt, int nOStr);
    void build();
    void insert(int substr, int index);
    void delete_str(int substr);
    void print(node* root);
    std::pair<node*,int> searchStr(node* root, int str);
    void GraphTree();
    void GraphTreeRecurse(node* root, ostream &out, int h = 0);
    void setMaxReaches(node* actualNode = root);
    void mrpAuxiliar(int str, int index);
    node* getRoot();
    string* getText();
};