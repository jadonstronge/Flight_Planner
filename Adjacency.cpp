//
// Created by jadon on 10/20/2021.
//

#include "Adjacency.h"
#include <fstream>
#include <iostream>
using namespace std;

void Adjacency::readIn(char * arg) {
    std::ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
    }
    char buffer[100];
    infs.getline(buffer, 100, '\n'); // buffer stores the amt of rows in file
    infs.getline(buffer, 100, ' '); // write over buffer, store first originating city
    while(!infs.eof()) {
        origin = buffer;
        infs.getline(buffer, 100, ' ');
        destination = buffer;
        infs.getline(buffer, 100, ' ');
        cost = stoi(buffer);
        infs.getline(buffer, 100, ' ');
        minutes = stoi(buffer);
        infs.getline(buffer, 100, '\n');
        airline = buffer;

        //wrap destination attributes in Wrapper object and insert to adj list
        populate_list(origin, destination, cost, minutes, airline);
        //swap origin and destination to account for bidirectional flights
        std::swap(origin, destination);
        populate_list(origin, destination, cost, minutes, airline);
        infs.getline(buffer, 100, ' ');
    }
    infs.close();
    /**comment out to view adjacency list**/
//    print_list();
}

void Adjacency::populate_list(const DSString& orig, const DSString& dest, const int& cos,
                              const int& mins, const DSString& air) {

    Wrapper a(dest, cos, mins, air);
    auto itr = adj_list.find(orig);
    if (itr == adj_list.end()) {
        //if origin city doesn't exist in map,
        // create list of possible flight paths for that origin city
        list<Wrapper> one_d_list;
        one_d_list.push_back(a);
        adj_list[orig] = one_d_list;
    } else {
        //if origin city exists in map,
        // push possible flight plan into it's list
        adj_list[orig].push_back(a);
    }
}

//arg = input file arg2 = output file
void Adjacency::requests(char* arg, char* arg2) {
    ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
    }
    char buffer[100];
    infs.getline(buffer, 100, '\n'); // number of rows in file to later be read over
    infs.getline(buffer, 100, ' ');
    while (!infs.eof()) {
        origin = buffer;
        infs.getline(buffer, 100, ' ');
        destination = buffer;
        infs.getline(buffer, 100, '\n');
        boolean = buffer;
        backtrack(origin, destination, boolean);
        print_stack(arg2);
        infs.getline(buffer, 100, ' ');
    }
    infs.close();
}

//receives origin city, dest city, and the time OR cost sort/'bool'
void Adjacency::backtrack(const DSString& orig, const DSString& dest, const DSString& boo) {

    temp.push(orig); //push source city to stack
    //returns and holds l.list of source city's connections
    auto& hold = adj_list[temp.top().get_destination()];

    //if destination city is found, store flight path option
    if (temp.top().get_destination() == dest) {
        itinerary.push(temp);
        temp.pop();
    }
    else { //iterate over temp.top's connection cities
        for (auto itr: hold) {
            if (itr.get_destination() == dest) {
                temp.push(itr);
                itinerary.push(temp);
                temp.pop();
            }
            else {
                // if dest city can be reached by one of source city's connection cities
                if (adj_list[itr.get_destination()].find(dest) != -1) {
                    if (on_stack(itr, temp)) {
                        continue;
                    } else {
                        temp.push(itr);
                        temp.push(dest);
                        itinerary.push(temp);
                        temp.pop(); temp.pop();
                    }
                }
            }
        }
    } //end of connections iteration

    temp.pop(); //clear temp for next request

} //end of function

/** function call may prove to be redundant as wrappers of the same city have different attributes
 * e.g. the first request checks two different austin flights from dallas to houston
 *      so it wouldn't matter that austin is already on the stack. additionally, we pop the first austin
 *      off anyway, so it'll never be on the stack when we check */

// checks if connection is already on stack
bool Adjacency::on_stack(Wrapper& itr, DSStack<Wrapper> temp) {
    while (!temp.is_empty()) {
        if (temp.top() == itr) {
            return true;
        }
        temp.pop();
    }
    return false;
}

void Adjacency::print_list(){
    for (const auto& itr: adj_list) {
        cout << "Source City: " << itr.first << endl;
        auto hold = itr.second;
        cout << "Destination Cit(y/ies): ";
        for (auto itr2: hold) {
            cout << " -> " << itr2.get_destination();
        }
        cout << "\n\n";
    }
}

void Adjacency::print_stack(char* arg) {

    while (!itinerary.is_empty()) {
        int total_time = 0; int total_cost = 0; int layovers = 0;
        auto hold1 = itinerary.top();

        DSStack<Wrapper> hold2; //flip the stack to print elements in order
        while (!hold1.is_empty()) {
            hold2.push(hold1.top());
            hold1.pop();
            layovers++;
        }
        layovers -= 2; //decrement layovers by 2 to account for orig and destination city

        cout << "Itinerary:" << "\n\t";
        cout << hold2.top().get_destination(); hold2.pop();
        while(!hold2.is_empty()) {
            cout << " -> " << hold2.top().get_destination();
            /*cout << " (" << hold2.top().get_airline() << ") ";*/
            total_time += hold2.top().get_minutes();
            total_cost += hold2.top().get_cost();
            hold2.pop();
        }
        total_time += layovers * 43; //layover incurs 43 min penalty
        total_cost += layovers * 23; //passenger spends avg $23 during layover
        cout << "\n\t";
        cout << "Total Time: " << total_time << " and Total Cost: " << total_cost;
        cout << "\n\n";
        itinerary.pop();
    }
}