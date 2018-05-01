#include <iostream>
#include <cstdlib>
#include "Leave.hpp"
#include "Date.hpp"
#include "Staff.hpp"
#include "LeaveSystem.hpp"
#include "LinkedList.h"

using namespace std;

bool operator< (const Date& d1, const Date& d2) {
    if(d1.getY() < d2.getY()){
        return true;
    } else if (d1.getY() == d2.getY()){
        if(d1.getM() < d2.getM()){
            return true;
        } else if (d1.getM() == d2.getM()){
            return d1.getD() < d2.getD();
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool operator< (const Leave& L1, const Leave& L2) {
    return L1.getFrom() < L2.getFrom();
}

int main(){
    LeaveSystem ls;
    int operation;

    do{
        cout << "Welcome to Leave Management System.\n"
        << "Done by MOHD ARIF DANIAL BIN ABDUL AZIZ\n"
        << "ID: 1142702426\tSECTION: TC201\n"
        << "\nPlease key in the number of the operation that you want to perform.\n"
        << "1. Add New Staff\n"
        << "2. Retrieve Staff Info\n"
        << "3. Apply a Leave\n"
        << "4. Approve a Leave\n"
        << "5. Reject a Leave\n"
        << "6. Update a Leave's application info\n"
        << "7. Cancel a Leave\n"
        << "8. Check a Leave status\n"
        << "\n-->";

        cin >> operation;

        system("cls");

        switch(operation){
        case 1:
            ls.addNewStaff();
            break;
        case 2:
            ls.retrieveStaffInfo();
            break;
        case 3:
            ls.applyLeave();
            break;
        case 4:
            ls.approveLeave();
            break;
        case 5:
            ls.rejectLeave();
            break;
        case 6:
            ls.updateLeaveInfo();
            break;
        case 7:
            ls.cancelLeave();
            break;
        case 8:
            ls.checkLeaveStatus();
            break;
        default:
            cout << "\nMESSAGE: Out of boundary input. Have a good day.";
            break;
        }
        system("pause");
        system("cls");
    }while(operation > 0 && operation < 9);

    return 0;
}


/*
Problem Statement

The Human Capital Management of MMU has appointed
you as the programmer to develop a leave management system
for the entire university. The system must be able to
manage and keep track of leaves applied by all university staff;
the staff can be an academician, executive, non-executive, etc.
The system should provide a main interface for a staff to apply leave,
check leave status, check leave balance and retrieve previous leave records.
If possible, the system could also be featured with analysis functions
such as number of staff (per faculty or department) on leave on a specific day,
staff who took medical leave more than a user-defined number of days,
total leave per faculty on a monthly basis, etc.
These features are useful to the management to monitoring purpose.
The requirements and specifications of the system can be outlined as follows:

Note: The data fields stated above are merely the minimum info
required by the system.
You may add any new data fields / functions that you deem appropriate.

Submission Format

1.	Submit the TC201_1142702426_MohdArifDanial.zip.zip file into the assignment submission system in the MMLS. Please adhere to the given deadline as late submission will be rejected by the server.
*/
