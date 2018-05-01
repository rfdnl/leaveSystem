#include "Leave.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>

bool Leave::approve(string approver){
    if (isPending()){
        status = "APPROVED";
        this->approver = approver;
        return true;
    } else {
        return false;
    }
}

bool Leave::reject(){
    if (isPending()){
        status = "REJECTED";
        return true;
    } else {
        return false;
    }
}

bool Leave::update(string& leaveType, string& reason, Date& from, Date& to){
    if (isPending()){
        this->leaveType = leaveType;
        this->reason = reason;
        this->from = Date(from.getD(),from.getM(),from.getY());
        this->to = Date(to.getD(),to.getM(),to.getY());
        return true;
    } else {
        return false;
    }
}

bool Leave::isPending(){
    return status == "PENDING";
}

string Leave::getName() const { // to check the owner of the Leave application
    return name;
}

Date Leave::getFrom() const { // for operator< overloading, main.cpp
    return from;
}

int Leave::getDuration(){
    return from.getDifference(to);
}

string Leave::print(bool withStatus){ // for terminal
    std::stringstream ss;
    ss << "  Name:\t\t" + name +
    "\n\t  From:\t\t" << from.print() <<
    "\n\t  To:\t\t" << to.print() <<
    "\n\t  Type:\t\t" << leaveType <<
    "\n\t  Reason:\t" << reason;

    if (withStatus){
        ss <<
        "\n\t  Approver:\t" << approver <<
        "\n\t  Duration:\t" << getDuration() << " day(s)"
        "\n\t  STATUS:\t" << status;
    }
    ss<< "\n";
    return ss.str();
}

string Leave::toString(){ // for text file
    std::stringstream ss;
    ss << name << " " << from.toString() << " " << to.toString() << " "
    << leaveType << " " << reason << " " << approver << " " << status << "\n";
    return ss.str();
}
