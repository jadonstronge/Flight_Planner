//
// Created by jadon on 10/22/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSSTACK_H
#define INC_21F_FLIGHT_PLANNER_DSSTACK_H

#include "list.h"
using namespace smulib;

template <typename T>

class DSStack {

private:
    list<T> data;
public:

    DSStack() = default;

    //adds element to the top of the stack
    void push(const T arg) {
        data.push_back(arg);
    }
    //removes element at the top of the stack
    void pop() {
        data.pop();
    }
    bool is_empty() {
        return (data.size() == 0);
    }
    // checks the tail of the list
    T& top() const {
        return data.top();
    }

};


#endif //INC_21F_FLIGHT_PLANNER_DSSTACK_H
