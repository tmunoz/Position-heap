#include "node.h"
#include "childtable.h"

node::node(){}

node::node(int s, int i) {
    str = s;
    index = i;
    child = new childtable();
}

int node::getIndex(){
    return index;
}

int node::getStr(){
    return str;
}
