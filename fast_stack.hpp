//
// Created by Thomas Muñoz on 24-12-17.
//

#ifndef RESEARCH_FAST_STACK_HPP
#define RESEARCH_FAST_STACK_HPP

#include <stack>

class Fast_stack{
    int counter;
    std::stack<long long int> collection;

public:
    Fast_stack(){
        counter=0;
    }

    void add_deleted(long long int str){
        collection.push(str);
    }

    bool isCollectionEmpty(){
        return collection.empty();
    }

    long long int get_index(){
        if (!collection.empty()){
            long long int str_index = collection.top();
            collection.pop();
            return str_index;
        }

        return counter++;
    }
};
#endif //RESEARCH_FAST_STACK_HPP
