#include <vector>
#include <utility>
#include <unordered_map>
#include "fast_stack.hpp"

class node;
class childtable;

using namespace std;

// These lines (12-22) allow using a pair as a key for unordered_map. Must check the hash function bounds
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};
// ================================================================

class heap {
    std::unordered_map<std::pair<int, int>, node*, pair_hash> maxReach; // An unordered_map is used because it's space optimal
    // and has average constant time complexity
    int numberOfStrings;
    node *root;
    vector<string> text;
    Fast_stack fstack;
public:

    heap();

    void insert(int substr, int index);

    void insert_str(string str);

    void delete_str(int substr);

    vector<node*> search(string pattern);

    void print(node *root);

    std::pair<node *, int> searchStr(node *root, int str);

    void GraphTree();

    void GraphTreeRecurse(node *root, ostream &out, int h = 0);

    void setMaxReaches();

    void mrpAuxiliar(int str, int index);

    node *getRoot();

    vector<string> getText();
};