#include <vector>
#include <utility>
#include <unordered_map>

class node;
class childtable;

using namespace std;

// These lines (11-30) allow using a pair as a key for unordered_map. Must check the hash function bounds
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template<typename S, typename T> struct hash<pair<S, T>>
    {
        inline size_t operator()(const pair<S, T> & v) const
        {
            size_t seed = 0;
            ::hash_combine(seed, v.first);
            ::hash_combine(seed, v.second);
            return seed;
        }
    };
}
// ================================================================

class heap {
    std::unordered_map<std::pair<int, int>, node*> maxReach; // An unordered_map is used because it's space optimal
    // and has average constant time complexity
    int numberOfStrings;
    node *root;
    string *text;
public:
    heap(string *txt, int nOStr);

    void build();

    void insert(int substr, int index);

    void delete_str(int substr);

    void print(node *root);

    std::pair<node *, int> searchStr(node *root, int str);

    void GraphTree();

    void GraphTreeRecurse(node *root, ostream &out, int h = 0);

    void setMaxReaches();

    void mrpAuxiliar(int str, int index);

    node *getRoot();

    string *getText();
};