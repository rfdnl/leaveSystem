#ifndef STAFF_HPP_INCLUDED
#define STAFF_HPP_INCLUDED

#include "LinkedList.h"
#include "Leave.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;

class Staff{
    friend istream& operator>> (istream& is , Staff& ob){
        is >> ob.id >> ob.name >> ob.position >> ob.category
        >> ob.phone >> ob.faculty >> ob.leaveBalance;
        return is;
    }
    string name;
    string id;
    string position;
    string category;
    string phone;
    string faculty;
    int leaveBalance;
    LinkedList<Leave*>* leaveRecords = new LinkedList<Leave*>();
public:
    Staff(string name="", string id="", string position="", string category="", string phone="", string faculty="", int leaveBalance = 20)
    :name(name), id(id), position(position), category(category), phone(phone), faculty(faculty), leaveBalance(leaveBalance){}
    bool canApply();
    bool haveLeaves();
    bool tryGetLeave(int index);
    void insertLeave(Leave* leave);
    void addNewLeave();
    void removeLeave(int index);
    void approve(int index, string approver);
    void reject(int index);
    void update(int index);
    string getName() const ;
    string print(bool withLeaves);
    string print(int index);
    string toString(bool staffOnly);
};

#endif // STAFF_HPP_INCLUDED

/*
Other than these, it should contain a list that stores the leave information of the staff.
For example, the list has all the leave records applied by the staff.
Implement the list using pointer-based linked list and sort them according to the date.
The list allows operations such as insertion, deletion, update at any position of the list.
*/
