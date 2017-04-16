#include <vector>

using namespace std;

class childtable;

class node {
private:
    int str, index;
public:
    childtable* child;
    node();
    node(int s, int i);
    int getStr();
    int getIndex();
};
