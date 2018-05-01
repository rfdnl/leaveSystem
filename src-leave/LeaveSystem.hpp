#ifndef LEAVESYSTEM_HPP_INCLUDED
#define LEAVESYSTEM_HPP_INCLUDED

#include "LinkedList.h"
#include "Staff.hpp"
#include <string>

using std::string;

class LeaveSystem{
    string staffFilename;
    string leaveFilename;
    LinkedList<Staff*>* staffList = new LinkedList<Staff*>();
    bool haveStaffs();
    bool tryGetStaff(int);
public:
    LeaveSystem(){
        staffFilename = "Staffs.txt";
        leaveFilename = "Leaves.txt";
        load();
    }
    void save(); //
    void load(); //


    void addNewStaff(); //
    void retrieveStaffInfo(); //
    void applyLeave(); //
    void approveLeave(); //
    void rejectLeave(); //
    void cancelLeave(); //
    void checkLeaveStatus(); //
    void updateLeaveInfo();
    void displayStaffs(); //
};

#endif // LEAVESYSTEM_HPP_INCLUDED
