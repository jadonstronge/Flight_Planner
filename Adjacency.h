//
// Created by jadon on 10/20/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_ADJACENCY_H
#define INC_21F_FLIGHT_PLANNER_ADJACENCY_H
#include "DSString.h"
#include "DSStack.h"
#include "Wrapper.h"
#include <map>
#include "list.h"
using namespace smulib;

class Adjacency {
private:

    std::map<DSString,list<Wrapper>> adj_list;
    DSStack<Wrapper> temp; //holds the cities that are pushed and popped as you backtrack
    DSStack<DSStack<Wrapper>> itinerary; //holds the final possible flight paths

    DSString origin, destination, boolean;
    DSString cost, minutes, airline;

public:
    void readIn(char*);
    void populate_list(const DSString&, const DSString&, const DSString&,
                       const DSString&, const DSString&);
    void requests(char*, char*);
    void backtrack(const DSString&, const DSString&, const DSString&);
    static bool on_stack(Wrapper&, DSStack<Wrapper>);
    void print_stack(char*);
    void print_list();
};


#endif //INC_21F_FLIGHT_PLANNER_ADJACENCY_H
