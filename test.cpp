//
// Created by jadon on 9/7/2021.
//
#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"
#include "list.h"
#include "DSStack.h"
using namespace smulib;

TEST_CASE("All DSString functions being tested", "[DSString]") {

    DSString one("My name is Jadon Stronge");
    DSString two("My name is Jadon Stronge");
    DSString three("My name is jadon stronge");
    DSString four("Jadon Stronge is my name");

    SECTION("overloaded assignment operator") {
        DSString test;
        test = one;
        REQUIRE(one == test);
        test = two;
        REQUIRE(two == test);
        REQUIRE(one == two);
    }

    SECTION("overloaded string concatenation") {
        DSString test("!");
        one = one + test;
        two = two + test;
        three = three + test;
        REQUIRE(one == "My name is Jadon Stronge!");
        REQUIRE(two == "My name is Jadon Stronge!");
        REQUIRE(three == "My name is jadon stronge!");
    }

    SECTION("overloaded equality operators") {
        REQUIRE(one == two);
        REQUIRE(!(one == three));
        REQUIRE(!(one == four));
    }

    SECTION("overloaded greater than operator") {
        REQUIRE(three > one);
        REQUIRE(three > four);
        REQUIRE(one > four);
    }

    SECTION("overloaded less than operator") {
        DSString test("a");
        REQUIRE(two < three);
        REQUIRE(four < three);
        REQUIRE(test > three);
    }

    SECTION("overloaded index operator") {
        REQUIRE(one[0] == 'M');
        REQUIRE(three[11] == 'j');
        REQUIRE(four[0] == 'J');
    }

    SECTION("returns string length") {
        DSString test("!");
        REQUIRE(one.length() == 24);
        one = one + test;
        REQUIRE(one.length() == 25);
        REQUIRE(test.length() == 1);
    }

    //substring method test
    SECTION("tokenizes string by x amount of chars starting from index") {
        REQUIRE(one.substring(0,1) == "M");
        REQUIRE(one.substring(0,11) == "My name is ");
        REQUIRE(one.substring(11, 1) == "J");
    }

    SECTION("overloaded insertion operator") {
        REQUIRE(std::cout << one << std::endl);
        REQUIRE(std::cout << three << std::endl);
        REQUIRE(std::cout << four << std::endl);
    }

    SECTION("returns index of first occurrence of a char") {
        REQUIRE(one.find_first('J') == 11);
        REQUIRE(two.find_first(' ') == 2);
        REQUIRE(four.find_first('i') == 14);
    }

    SECTION("returns index of last occurrence of a char") {
        REQUIRE(one.find_last('e') == 23);
        REQUIRE(three.find_last('n') == 21);
        REQUIRE(four.find_last('a') == 21);
    }

    SECTION("returns index of first occurrence of char starting at index") {
        REQUIRE(one.find(5, 'a') == 12);
        REQUIRE(three.find(7, 'e') == 23);
        REQUIRE(four.find(5, 'n') == 10);
    }

    SECTION("finds first occurrence of substring in char array") {
        DSString test("!");
        REQUIRE(one.find("Jadon"));
        REQUIRE(two.find("Stronge"));
        REQUIRE(!four.find("name!"));
    }

    SECTION("makes all characters of string lowercase") {
        DSString test("wHaTsUp");
        REQUIRE(one.to_lower() == "my name is jadon stronge");
        REQUIRE(four.to_lower() == "jadon stronge is my name");
        REQUIRE(test.to_lower() == "whatsup");
    }
}

TEST_CASE("All DSVector functions being test", "[DSVector]") {

    DSVector<int> one;
    DSVector<int> two;
    DSVector<DSString> three;

    SECTION("test pushback and at() functions") {
        two.push_back(1);
        REQUIRE(two.at(0) == 1);
        two.push_back(5);
        REQUIRE(two.at(1) == 5);
        two.push_back(10);
        REQUIRE(two.at(2) == 10);
    }

    SECTION("test pushfront and index functions") {
        two.push_front(1);
        two.push_front(5);
        two.push_front(10);
        REQUIRE(two[2] == 1);
        REQUIRE(two[0] == 10);
        REQUIRE(two[1] == 5);
    }

    SECTION("inserts element at specified index") {
        one.insert(0, 1);
        REQUIRE(one.at(0) == 1);
        one.insert(0, 2);
        DSString hello("hello");
        three.insert(0, hello);
        REQUIRE(one[0] == 2);
        REQUIRE(three.at(0) == "hello");
    }

    SECTION("test is_clear boolean function") {
        REQUIRE(one.is_clear() == true);
        REQUIRE(two.is_clear() == true);
        DSString hello("hello");
        three.push_back(hello);
        REQUIRE(three.is_clear() == false);
    }

    SECTION("tests the size function") {
        one.push_back(1);
        two.push_back(2);
        REQUIRE(one.the_size() == 1);
        REQUIRE(two.the_size() == 1);
        REQUIRE(three.the_size() == 0);
    }

    SECTION("test overloaded assignment operator") {
        one.push_back(1); one.push_back(0); one.push_back(-1);
        two = one;
        REQUIRE(two.the_size() == 3);
        REQUIRE(two.at(0) == 1);
        REQUIRE(two[2] == -1);
    }

    SECTION("find function returns index of element or -1 if not found") {
        one.push_back(1); one.push_back(11);
        REQUIRE(one.find(11) == 1);
        REQUIRE(one.find(1) == 0);
        REQUIRE(one.find(100) == -1);
    }
}

TEST_CASE("All doubly linked list functions being tested", "[list]") {

    list<int> one;
    list<int> two;
    list<DSString> three;
    SECTION("tests insert function, copy constructor, and overloaded assignment") {
        one.push_back(1);
        one.push_back(3);
        one.insert(1, 2);
        REQUIRE(one[1] == 2);

        list<int> temp(one);
        REQUIRE(temp[1] == 2);

        DSString first_name("Jadon");
        three.push_back(first_name);
        list<DSString> temp2 = three;
        REQUIRE(temp2.at(0) == "Jadon");

        DSString last_name; last_name = "Stronge";
        temp2.push_back(last_name);
        DSString middle_name; middle_name = "David";
        temp2.insert(1, middle_name);
        REQUIRE(temp2.at(1) == "David");
    }

    SECTION("tests push_back and return size function") {
        one.push_back(500);
        DSString first_name("Jadon");
        three.push_back(first_name);
        DSString last_name; last_name = "Stronge";
        three.push_back(last_name);

        REQUIRE(one.size() == 1);
        REQUIRE(three.size() == 2);
        REQUIRE(two.size() == 0);
    }

    SECTION("tests push_front, subscript, and at function") {
        one.push_front(1);
        one.push_front(2);
        one.push_front(3);
        REQUIRE(one.at(0) == 3);
        REQUIRE(one.at(2) == 1);
        REQUIRE(one[1] == 2);
    }

    SECTION("tests top function") {
        one.push_back(1);
        REQUIRE(one.top() == 1);
        one.push_back(2);
        REQUIRE(one.top() == 2);
        one.push_back(3);
        REQUIRE(one.top() == 3);
    }

    SECTION("tests pop function") {
        one.pop();
        REQUIRE(one.get_head() == one.get_tail());
        REQUIRE(one.size() == 0);
        one.push_back(1); one.pop();
        REQUIRE(one.get_head() == one.get_tail());
        REQUIRE(one.size() == 0);
        one.push_back(1); one.push_back(2); one.pop();
        REQUIRE(one.size() == 1);
    }
}

TEST_CASE("Tests all functions in stack class", "[DSStack]") {
    DSStack<int> one;
    DSStack<int> two;
    DSStack<DSString> three;

    SECTION("tests push function") {
        one.push(1);
        one.push(2);
        one.push(3);
    }
}