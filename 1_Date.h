#pragma once

#include <iostream>
#include <sstream>

const char SLASH = '/';
enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
const int daysInMonths[]{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isInInterval(int x, int a, int b);

class Date {
    int day = 0;
    int month = 0;
    int year = 0;

    private:
        bool isValid(int d, int m, int y) const; //checks validity of entered date, years divisible by four are leap years

    public:
        Date() = default; //d = 0, m = 0, y = 0

        Date(int d, int m, int y); //if d, m, y is invalid, Date is set to invalid ("00/00/0000")

        void setDate(int d, int m, int y); //if d, m, y is invalid, Date is set to invalid ("00/00/0000")

        std::string getDate() const; //return "00/00/0000" when date is incorrect

        bool isEmpty() const; //date was incorrect or Date was constructed with no parameters

        bool operator<(const Date &inputDate) const; //compares two Dates, returns true if first Date is earlier

        bool operator==(const Date &inputDate) const; //compares two Dates, returns true if both d, m, y are equal

        Date operator+(int newDays) const; //adds newDays to existing date; negative newDays argument is ignored, returns original Date
};

std::istream &operator>>(std::istream &is, Date &inputDate); //loads string in date format ("12/03/2002") into Date object