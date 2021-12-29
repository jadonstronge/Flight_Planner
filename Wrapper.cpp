//
// Created by jadon on 10/20/2021.
// class wraps attributes of a flight (destination, cost, length of flight, etc.),
// to be stored in an adjacency list in separate file
//

#include "Wrapper.h"

Wrapper::Wrapper() {
    destination = "";
    cost = 0;
    minutes = 0;
    airline = "";
}
Wrapper::Wrapper(const DSString& dest, const int& c, const int& mins, const DSString& air) {
    destination = dest;
    cost = c;
    minutes = mins;
    airline = air;
}

//one param constructor designed for backtrack function
Wrapper::Wrapper(const DSString & orig) {
    destination = orig;
}

DSString &Wrapper::get_destination() {
    return destination;
}

int& Wrapper::get_cost() {
    return cost;
}

int& Wrapper::get_minutes() {
    return minutes;
}

DSString &Wrapper::get_airline() {
    return airline;
}

bool Wrapper::operator==(const Wrapper &rhs) const {
    return ((destination == rhs.destination));
}