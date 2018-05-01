#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

int Date::getD() const { return this->d; }

int Date::getM() const { return this->m; }

int Date::getY() const { return this->y; }

int Date::countLeapYears(Date& date){
    int years = date.getY();
    if (d<=2) years--;

    return years/4 - years/100 + years/400;
}

void Date::operator= (const Date& date){
    this->d = date.getD();
    this->m = date.getM();
    this->y = date.getY();
}

int Date::getDifference(Date& date){
    long int num1 = y*365 + d;
    for (int i=0; i < m-1; i++){
        num1 += month[i];
    }
    num1 += countLeapYears(*this);

    long int num2 = date.getY()*365 + date.getD();
    for (int i=0; i< date.getM()-1; i++){
        num2 += month[i];
    }
    num2 += countLeapYears(date);

    return (num2 - num1);
}

std::string Date::toString(){
    std::stringstream ss;
    ss << this->d << " " << this->m << " " << this->y;
    return ss.str();
}

std::string Date::print(){
    std::stringstream ss;
    ss << this->d << "/" << this->m << "/" << this->y;
    return ss.str();
}
