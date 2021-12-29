//
// Created by jadon on 10/20/2021.
// class wraps attributes of a flight (destination, cost, length of flight, etc.),
// to be stored in an adjacency list in separate file
//

#ifndef INC_21F_FLIGHT_PLANNER_WRAPPER_H
#define INC_21F_FLIGHT_PLANNER_WRAPPER_H
#include "DSString.h"
#include <iostream>
#include <vector>
#include "list.h"
using namespace smulib;

class Wrapper {
private:
    DSString destination, airline;
    int cost, minutes;

public:
    Wrapper();
    Wrapper(const DSString&, const int&, const int&, const DSString&);
    Wrapper(const DSString&); //to make an object for source city to push onto stack

    DSString& get_destination();
    int& get_cost();
    int& get_minutes();
    DSString& get_airline();

    bool operator==(const Wrapper&) const;
    ~Wrapper() = default;
};


#endif //INC_21F_FLIGHT_PLANNER_WRAPPER_H
