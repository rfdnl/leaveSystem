#ifndef DATE_HPP_INCLUDED
#define DATE_HPP_INCLUDED
#include <iostream>
#include <vector>
using std::istream;

class Date
{
    friend std::istream& operator>> (istream& is, Date& date){
        is >> date.d >> date.m >> date.y;
        return is;
    }
    const int month[12] = {31,28,31,30,31,30,
                        31,31,30,31,30,31};

    int d; //dd
    int m; //mm
    int y; //yyyy
    int countLeapYears(Date& date);

public:
    Date(int d = 1, int m = 1, int y = 1990):d(d), m(m), y(y){};
    void operator= (const Date& date);
    int getD() const;
    int getM() const;
    int getY() const;
    int getDifference(Date&);
    std::string toString();
    std::string print();
};

#endif // DATE_HPP_INCLUDED
