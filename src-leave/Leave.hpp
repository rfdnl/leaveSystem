#ifndef LEAVE_HPP_INCLUDED
#define LEAVE_HPP_INCLUDED
#include "Date.hpp"
#include <sstream>
#include <iostream>

using std::string;

class Leave{
    friend istream& operator>> (istream& is, Leave& ob){
        is >> ob.name >> ob.from >> ob.to >> ob.leaveType
        >> ob.reason >> ob.approver >> ob.status;
        return is;
    }
    string name;
    Date from;
    Date to;
    string leaveType;
    string reason;
    string approver;
    string status;
    bool isPending();

public:
    Leave(string name = "", Date from = Date(1,1,1990), Date to = Date(1,1,1990), string leaveType = "", string reason = ""):
        name(name), from(from), to(to), leaveType(leaveType), reason(reason){
            approver = "N/A";
            status = "PENDING";
        }
    bool approve(string);
    bool reject();
    bool update(string&,string&,Date&,Date&);
    string getName() const;
    Date getFrom() const;
    int getDuration();
    string print(bool withStatus);
    string toString();
};

#endif // LEAVE_HPP_INCLUDED
