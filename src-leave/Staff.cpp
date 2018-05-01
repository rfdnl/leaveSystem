#include "Staff.hpp"
#include "LinkedList.h"
#include "Leave.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::stringstream;

bool Staff::canApply(){
    return leaveBalance > 0;
}

bool Staff::haveLeaves(){
    if (leaveRecords->getLength() > 0){
        return true;
    } else {
        cout << "\n" << getName() << " does not have any Leave application. Please apply for a new one to begin.\n";
        return false;
    }
}

bool Staff::tryGetLeave(int index){
    if (1 <= index && index <= leaveRecords->getLength()){
        return true;
    } else {
        cout << "\nIndex entered is out of boundary.\n";
        return false;
    }
}

void Staff::insertLeave(Leave* leave){ //for Load, LeaveSystem.xpp
    leaveRecords->sortInsert(leave);
}

void Staff::addNewLeave(){
    if (canApply()){
        string leaveType, reason;
        Date from, to;

        cout << "\n\nApplying Leave for " << getName() << ".";
        cout << "\n\n(Please enter one-word, camelCase or Under_Score input only)\nLEAVE Type\n--> "; cin >> leaveType;
        cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nREASON\n--> "; cin >> reason;
        cout << "\n(dd mm YYYY)\nFROM\n--> "; cin >> from;
        cout << "\n(dd mm YYYY)\nTO\n--> "; cin >> to;

        if (from.getDifference(to) <= leaveBalance){
            Leave* leave = new Leave(getName(),from,to,leaveType,reason);
            insertLeave(leave);
        } else {
            cout << "\nMESSAGE: Leave application aborted, leave duration applied is bigger than leave balance.\n";
        }
    } else {
        cout << "\nMESSAGE: " << name << " have used up all the leaves.\n";
    }
}

void Staff::approve(int index, string approver){ // will approve leave application at index
    if (leaveRecords->getEntry(index)->approve(approver)){
        leaveBalance = leaveBalance - leaveRecords->getEntry(index)->getDuration();
    } else cout << "\nMESSAGE : Leave record is not pending for approval.\n";
}


void Staff::reject(int index){ // will reject leave based on index
    if (leaveRecords->getEntry(index)->reject()){
        leaveBalance = leaveBalance + leaveRecords->getEntry(index)->getDuration();
    } else cout << "\nMESSAGE : Leave record is not pending for approval.\n";
}

void Staff::update(int index){ // will update leave's info based on index
    string leaveType, reason;
    Date from, to;

    cout << "Current " << getName() << "'s Leave's info.\n";
    cout << leaveRecords->getEntry(index)->print(true);

    cout << "\nUpdating Leave for " << getName() << ".";
    cout << "\n\n(Please enter one-word, camelCase or Under_Score input only)\nLEAVE TYPE\n--> "; cin >> leaveType;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nREASON\n--> "; cin >> reason;
    cout << "\n(dd mm YYYY)\nFROM\n--> "; cin >> from;
    cout << "\n(dd mm YYYY)\nTO\n--> "; cin >> to;

    if (from.getDifference(to) <= leaveBalance){
        if (leaveRecords->getEntry(index)->update(leaveType, reason, from, to)){
            cout << "\n\tUPDATED!";
            cout << leaveRecords->getEntry(index)->print(true);
        } else {
            cout << "Updating Leave's Info aborted. Old Leave application is not PENDING anymore.";
        }
    } else {
        cout << "\nMESSAGE: Updating Leave's Info aborted. Leave duration applied is bigger than leave balance.\n";
    }
}

void Staff::removeLeave(int index){ // will remove leave record from leaveList
    if (!(leaveRecords->remove(index)))
        cout << "\nMESSAGE : Cannot remove. Index out of boundary.\n";
}

string Staff::getName() const {
    return name;
}

string Staff::print(bool withLeaves){ // this will print all records the staff has, not with status
    stringstream ss;

    ss << "  Name: " << name <<
    ", ID: " << id;

    if (withLeaves){
        ss << "\n\n  Position:\t" << position <<
        "\n  Category:\t" << category <<
        "\n  Phone: \t" << phone <<
        "\n  Faculty: \t" << faculty
        << "\n  Leaves :\t"<< leaveBalance <<"\n";

        for(int i=1;i<=leaveRecords->getLength();i++){
            ss << "\n\t" << i << ")";
            ss << leaveRecords->getEntry(i)->print(false);
        }
    }

    ss << "\n";
    return ss.str();
}

string Staff::print(int index){ // this will print single record + status
    if (0 < index && index <= leaveRecords->getLength()){
        return leaveRecords->getEntry(index)->print(true);
    } else {
        return "\nMESSAGE : Cannot print. Index out of boundary!";
    }
}

string Staff::toString(bool staffOnly){ //for text file
    stringstream ss;
    if (staffOnly){
        ss << id << " " << name << " " << position << " " << category
        << " " << phone << " " << faculty << " " << leaveBalance << endl;
    } else {
        for(int i=1;i<=leaveRecords->getLength();i++){
            ss << leaveRecords->getEntry(i)->toString();
        }
    }
    return ss.str();
}
