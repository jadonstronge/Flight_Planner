//
// Created by jadon on 6/9/2021.
//

#ifndef NOTES2_LIST_H
#define NOTES2_LIST_H
#include <iostream>

// name space prevents conflicting function names between classes
namespace smulib { // wrap all your classes into a library EX: DSString, and list, etc.

    template <typename T> // T is the generic data type
    // almost like a meta/placeholder data type

    // when implementing a class template, you CANNOT separate .h and .cpp
    class list {
    private:
//        list node represents the fundamental node structure of the linked list
        struct list_node { // like classes but w default visibility public (whereas class is default private)
            T data;
            list_node *next, *prev;
            explicit list_node(const T& arg, list_node* n = nullptr, // member-wise initialization
                      list_node* p = nullptr):
                    data(arg), next(n), prev(p) {}
        };

        list_node* front = nullptr;
        list_node* back = nullptr;

        int count_nodes = 0;

    public:
        list() = default;

        /** no need to explicitly set count nodes in copy constructor
         * or overloaded assignment operator because push_back increments count_nodes */
        //copy constructor
        list(const list<T>& rhs) {
            list_node* cur = rhs.front;
            while (cur != nullptr) {
                push_back(cur->data);
                cur = cur->next;
            }
        }

        list& operator=(const list<T>& rhs) {
            if (this == &rhs) {
                return *this;
            }
            list_node* cur = rhs.front;
            while (cur != nullptr){
                this->push_back(cur->data);
                cur = cur->next;
            }
            return *this;
        }

        ~list() {
            if (front == nullptr) {}
            else {
                while (front->next != nullptr) {
                    auto temp = front;
                    front = front->next;
                    delete temp;
                }
                delete front;
            }
        }

        int size() {return count_nodes;}

        void push_front(const T& value) { // const ref allows receiving literal, variable, or constant
            auto* temp = new list_node(value);

            // if front = null, then back = null. one can't be null and the other a value
            if (front == nullptr) {
                front = back = temp;
            }
            else {
                front -> prev = temp;
                temp -> next = front;
                front = temp;
            }
            count_nodes++;
        }

        void push_back(const T& value) {
            auto* temp = new list_node(value);

            // if front = null, then back = null. one can't be null and the other a value
            if (back == nullptr) {
                front = back = temp;
            }
            else {
                back -> next = temp;
                temp -> prev = back;
                back = temp;
            }
            count_nodes++;
        }

        void insert(int location, const T& val) {
            // throw exception if location is out of bounds of list
            if ((location >= count_nodes) || (location < 0)) {
                throw std::out_of_range("smulib::list::out of range");
            }
            else {
                list_node* cur = front;
                auto temp = new list_node(val);
                for (int i = 0; i < location; i++) {
                    cur = cur->next;
                }
                cur->prev->next = temp;
                temp->prev = cur->prev;
                temp->next = cur;
                cur->prev = temp;
                count_nodes++;
            }
        }

        T& at(int location) { // return by ref, so you can modify what's at that location
            // throw exception if location is out of bounds of list
            if ((location >= count_nodes) || (location < 0)) {
                throw std::out_of_range("smulib::list::out of range");
            }
            list_node* cur = front;
            // iterates to the exact location
            for (int i = 0; i < location; i++) {
                cur = cur -> next;
            }
            return cur -> data;
        }

        T& operator[](int location) {
            if ((location >= count_nodes) || (location < 0)) {
                throw std::out_of_range("smulib::list::out of range");
            }
            list_node* cur = front;
            // iterates to the exact location
            for (int i = 0; i < location; i++) {
                cur = cur -> next;
            }
            return cur -> data;
        }

        bool operator==(const list<T>& rhs) const {
            int count;
            list_node* cur = front;
            for(int i = 0; i < rhs.size(); i++) {
                if (cur->data == rhs[i]) {
                    count++;
                }
                cur = cur->next;
            }
            return (count == size());
        }

        void print_list() {
            list_node* cur = front;
            while (cur != nullptr) {
                std::cout <<  cur -> data << "-->";
                // we created cur pointer instead of using front point
                // because this line would've modified front's data
                cur = cur -> next;
            }
        }

        list<T>& reverse_list(){
            list<T> reverse;
            list_node* cur = front;
            while (cur != nullptr) {
                reverse.push_front(cur->data);
                cur = cur -> next;
            }
            return reverse;
        }

        //returns index of data or -1 if it doesn't exist
        int find(const T& arg) {
            list_node* cur = front;
            for (int i = 0; i < size(); i++) {
                if (cur->data == arg) {
                    return i;
                }
                else {
                    cur = cur->next;
                }
            }
            return -1;
        }

        list_node* get_head() {
            list_node* cur = front;
            return cur;
        }

        list_node* get_tail() {
            auto cur = back;
            return cur;
        }

        void pop() {
            if (size() == 0) {
                front = back = nullptr;
            }
            if (size() == 1) {
                list_node* cur = front;
                front = back = nullptr;
                delete cur;
            }
            if (size() > 1) {
                list_node* cur = back;
                back->prev->next = nullptr;
                back = back->prev;
                delete cur;
            }
            if (size() > 0) {
                count_nodes--;
            }
        }

        T & top() const {
            list_node* cur = back;
            return cur->data;
        }

        bool is_empty() {
            return (count_nodes == 0);
        }

        // iterator is a way to traverse a container from outside
        // that container's class
        class iterator {
        protected:
            list_node* cur = nullptr;
        public:

            //constructors //double check no arg constructor?!?
            iterator() {
                cur = nullptr;
            }
            explicit iterator(list_node* c) {
                cur = c;
            }
            iterator (const iterator& arg) {
                cur = arg.cur;
            }

            //overloaded assignment operator
            iterator& operator=(const iterator& arg) {
                if (this == &arg) {
                    return *this;
                }
                cur = arg.cur;
                return *this;
            }

            //overloaded de-reference operator
            T& operator*() {
                if (!cur) {
                    throw std::range_error("smulib::list::iterator cannot be de-referenced");
                }
                return cur -> data;
            }

            //overloaded increment operator - advance iterator from one element to next
            //pre-increment (increment variable value by 1 before assigning value to variable)
            iterator& operator++() {
                if (!cur) {
                    throw std::range_error("smulib::list::iterator cannot be de-referenced");
                }
                cur = cur -> next;
                return *this;
            }

            //overloaded equality operators -
            // - checks to see if the iterators are HOLDING the same address
            bool operator==(const iterator& arg) {
                return (cur == arg.cur);
            }
            bool operator!=(const iterator& arg) {
                return (cur != arg.cur);
            }
        };

        //outside iterator class
        iterator begin() {
            return iterator(front);
        }
        iterator end() {
            return iterator(back->next);
        }
    };
}

#endif //NOTES2_LIST_H


