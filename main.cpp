/**
 * Fall 2021 PA 04 - Flight Planner Template Repo.
 * Based on PA 02 Template repo
 */


/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "Adjacency.h"
/*#include "list.h"

#include "DSString.h"
#include <fstream>
#include <iostream>*/
using namespace std;

using namespace smulib;

int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
    }
    else {
        Adjacency a;
        a.readIn(argv[1]);
        a.requests(argv[2], argv[3]);
    }


    return 0;
}