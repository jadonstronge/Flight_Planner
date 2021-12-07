//
// Created by jadon on 10/20/2021.
// class wraps attributes of a flight (destination, cost, length of flight, etc.),
// to be stored in an adjacency list in separate file
//

#include "Wrapper.h"

Wrapper::Wrapper() {
    destination = "";
    cost = "";
    minutes = "";
    airline = "";
}
Wrapper::Wrapper(const DSString& dest, const DSString& c, const DSString& mins, const DSString& air) {
    destination = dest;
    cost = c;
    minutes = mins;
    airline = air;
}

//one param constructor designed for backtrack function to provide
// variable to name consistency when checking if cities on stack == final dest
Wrapper::Wrapper(const DSString & orig) {
    destination = orig;
}

DSString & Wrapper::get_destination() {
    return destination;
}

DSString &Wrapper::get_cost() {
    return cost;
}

DSString &Wrapper::get_minutes() {
    return minutes;
}

DSString &Wrapper::get_airline() {
    return airline;
}

bool Wrapper::operator==(const Wrapper &rhs) const {
    return ((destination == rhs.destination));
}

bool Wrapper::has_visited(const Wrapper & arg) {
    for (const auto& itr: visitedCities) {
        if (itr == arg) {
            return true;
        }
    }
    return false;
}

void Wrapper::visit(const Wrapper &arg) {
    this->visitedCities.push_back(arg);
}
