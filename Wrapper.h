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
    DSString destination, cost, minutes, airline;
    std::vector<Wrapper> visitedCities;

public:
    Wrapper();
    Wrapper(const DSString&, const DSString&, const DSString&, const DSString&);
    Wrapper(const DSString&); //to make an object for source city to push onto stack

    DSString & get_destination();
    DSString& get_cost();
    DSString& get_minutes();
    DSString& get_airline();
    bool has_visited(const Wrapper&);
    void visit(const Wrapper&);

    bool operator==(const Wrapper&) const;
    ~Wrapper() = default;
};


#endif //INC_21F_FLIGHT_PLANNER_WRAPPER_H
