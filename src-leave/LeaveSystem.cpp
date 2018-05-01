#include "LeaveSystem.hpp"
#include "Leave.hpp"
#include "Date.hpp"
#include "Staff.hpp"
#include <iostream>
#include <fstream>

void LeaveSystem::save(){
    ofstream file1(staffFilename);
    if (file1.is_open()){
        for(int i=1; i<=staffList->getLength();i++){
            file1 << staffList->getEntry(i)->toString(true);
        }
        file1.close();
    } else cout << "\nMESSAGE: Unable to save staffs.\n";

    ofstream file2(leaveFilename);
    if (file2.is_open()){
        for(int i=1; i<=staffList->getLength();i++){
            file2 << staffList->getEntry(i)->toString(false);
        }
        file2.close();
    } else cout << "\nMESSAGE: Unable to save leaves.\n";
}

void LeaveSystem::load(){
    string line;
    ifstream file1(staffFilename);
    if (file1.is_open()){
        while (getline(file1, line)){
            Staff* staff = new Staff();
            std::istringstream iss(line);
            iss >> *staff;
            staffList->insertLast(staff);
        } file1. close();
    }

    ifstream file2(leaveFilename);
    if (file2.is_open()){
        while (getline(file2, line)){
            Leave* leave = new Leave();
            std::istringstream iss(line);
            iss >> *leave;
            for(int i=1; i <= staffList->getLength();i++){
                if (leave->getName() == staffList->getEntry(i)->getName()){
                    staffList->getEntry(i)->insertLeave(leave);
                    break;
                }
            }
        } file2.close();
    }
}

void LeaveSystem::addNewStaff(){
    cout << "\n\n\t[ADD NEW STAFF]\n";

    string name, id, position, category, phone, faculty;

    cout << "\nID      : "; cin >> id;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nNAME\n--> "; cin >> name;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nPOSITION\n--> "; cin >> position;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nCATEGORY\n--> "; cin >> category;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nPHONE\n--> "; cin >> phone;
    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nFACULTY/DEPARTMENT\n--> "; cin >> faculty;

    Staff* staff = new Staff(name, id, position, category, phone, faculty);
    staffList->insertLast(staff);
    save();
}

void LeaveSystem::retrieveStaffInfo(){ // along with Leave records
    cout << "\n\n\t[RETRIEVE STAFF INFO]\n";
    if (haveStaffs()){
        displayStaffs();

        int index;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> index;
        if (tryGetStaff(index)){
            cout << staffList->getEntry(index)->print(true);
        }
    }
}

void LeaveSystem::applyLeave(){
    cout << "\n\n\t[APPLY A LEAVE]\n";

    if (haveStaffs()){
        displayStaffs();

        int index;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> index;
        if (tryGetStaff(index)){
            staffList->getEntry(index)->addNewLeave();
            cout << staffList->getEntry(index)->print(true);
            save();
        }
    }
}

void LeaveSystem::approveLeave(){
    cout << "\n\n\t[APPROVE A LEAVE APPLICATION]\n";
    if (haveStaffs()){
        displayStaffs();

        int staff;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> staff;
        if (tryGetStaff(staff)){
            cout << staffList->getEntry(staff)->print(true);

            if (staffList->getEntry(staff)->haveLeaves()){
                int leave;
                cout << "\nPlease specify the index of the leave record that you want to APPROVE : ";
                cin >> leave;

                if (staffList->getEntry(staff)->tryGetLeave(leave)){
                    string approver;
                    cout << "\n(Please enter one-word, camelCase or Under_Score input only)\nPlease enter the name of the approver\n-->";
                    cin >> approver;
                    staffList->getEntry(staff)->approve(leave, approver);

                    cout << staffList->getEntry(staff)->print(leave);
                    save();
                }
            }
        }
    }
}

void LeaveSystem::rejectLeave(){
    cout << "\n\n\t[REJECT A LEAVE APPLICATION]\n";
    if (haveStaffs()){
        displayStaffs();

        int staff;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> staff;
        if (tryGetStaff(staff)){
            cout << staffList->getEntry(staff)->print(true);
            if (staffList->getEntry(staff)->haveLeaves()){
                int leave;
                cout << "\nPlease specify the index of the leave record that you want to REJECT : ";
                cin >> leave;

                if (staffList->getEntry(staff)->tryGetLeave(leave)){
                    staffList->getEntry(staff)->reject(leave);
                    cout << staffList->getEntry(staff)->print(leave);
                    save();
                }
            }
        }
    }
}

void LeaveSystem::cancelLeave(){
    cout << "\n\n\t[CANCEL A LEAVE APPLICATION]\n";
    if (haveStaffs()){
        displayStaffs();

        int staff;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> staff;
        if (tryGetStaff(staff)){
            cout << staffList->getEntry(staff)->print(true);
            if (staffList->getEntry(staff)->haveLeaves()){
                int leave;
                cout << "\nPlease specify the index of the leave record that you want to cancel : ";
                cin >> leave;
                if (staffList->getEntry(staff)->tryGetLeave(leave)){
                    staffList->getEntry(staff)->removeLeave(leave);
                    save();
                }
            }
        }
    }
}

void LeaveSystem::checkLeaveStatus(){
    cout << "\n\n\t[CHECKING A LEAVE STATUS]\n";
    if (haveStaffs()){
        displayStaffs();

        int staff;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> staff;
        if (tryGetStaff(staff)){
            cout << staffList->getEntry(staff)->print(true);
            if (staffList->getEntry(staff)->haveLeaves()){
                int leave;
                cout << "\nPlease specify the index of the leave record : ";
                cin >> leave;
                if (staffList->getEntry(staff)->tryGetLeave(leave)){
                    cout << staffList->getEntry(staff)->print(leave);
                }
            }
        }
    }
}

void LeaveSystem::updateLeaveInfo(){
    if (haveStaffs()){
        cout << "\n\n\t[UPDATING A LEAVE'S APPLICATION INFO]\n";
        displayStaffs();

        int staff;
        cout << "\nPlease specify the index (not ID) of the staff : ";
        cin >> staff;
        if (tryGetStaff(staff)){
            cout << staffList->getEntry(staff)->print(true);
            if (staffList->getEntry(staff)->haveLeaves()){
                int leave;
                cout << "\nPlease specify the index of the leave record : ";
                cin >> leave;
                if (staffList->getEntry(staff)->tryGetLeave(leave)){
                    staffList->getEntry(staff)->update(leave);
                }
            }
        }
    }
}

void LeaveSystem::displayStaffs(){
    cout << "\nINDEX ) \n";
    for(int i = 1; i <= staffList->getLength(); i++){
        cout << endl << i << ")";
        cout << staffList->getEntry(i)->print(false);
    }
}

bool LeaveSystem::haveStaffs(){
    if (staffList->getLength() > 0){
        return true;
    } else {
        cout << "\nList containing staffs' information is empty. Please add a new Staff to use this function.";
        return false;
    }
}

bool LeaveSystem::tryGetStaff(int index){
    if (1 <= index && index <= staffList->getLength()){
        return true;
    } else {
        cout << "\nIndex entered is out of boundary.\n";
        return false;
    }
}
