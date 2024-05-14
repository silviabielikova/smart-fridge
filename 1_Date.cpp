#include <iostream>
#include <iomanip>

#include "1_Date.h"


bool isInInterval(int x, int a, int b) {
    if (a <= x && x <= b) {
        return true;
    }
    return false;
}

Date::Date(int d, int m, int y) {
    if (isValid(d, m, y)) {
        day = d;
        month = m;
        year = y;
        return;
    }
}

void Date::setDate(int d, int m, int y) {
    if (isValid(d, m, y)) {
        day = d;
        month = m;
        year = y;
        return;
    }

    day = 0;
    month = 0;
    year = 0;
}

std::string Date::getDate() const {
    std::ostringstream output;
    output << std::setfill('0') << std::setw(2) << day << SLASH;
    output << std::setfill('0') << std::setw(2) << month << SLASH;
    output << std::setfill('0') << std::setw(4) << year;

    return output.str();
}

bool Date::isValid(int day0, int month0, int year0) const{
    if (!isInInterval(month0, JAN, DEC)) {
        return false;
    }

    if (!isInInterval(day0, 1, daysInMonths[month0 - 1])) {
        return false;
    }

    if (year0 < 0) {
        return false;
    }

    if (year % 4 != 0 && month0 == FEB) {
        if (day0 == 29) {
            return false;
        }
    }

    return true;
}

bool Date::operator<(const Date &inputTime) const {
    if (this->year != inputTime.year) {
        return this->year < inputTime.year;
    }

    if (this->month != inputTime.month) {
        return this->month < inputTime.month;
    }

    return this->day < inputTime.day;
}

Date Date::operator+(int newDays) const {
    if (newDays < 0) {
        return *this;
    }

    if (isValid(day + newDays, month, year)) {
        return Date(day + newDays, month, year);
    }

    int newDay = day;
    int newMonth = month;
    int newYear = year;

    int daysInMonth;
    while (newDays) {
        if (newMonth == FEB && newYear % 4 != 0) {
            daysInMonth = 28;
        }

        else {
            daysInMonth = daysInMonths[newMonth-1];
        }

        if (newDay + newDays <= daysInMonth) {
            newDay += newDays;
            break;
        }

        else {
            newDays -= (daysInMonth - newDay);
            newDay = 0;

            if (newMonth + 1 <= DEC) {
                newMonth++;
            }

            else {
                newMonth = JAN;
                newYear++;
            }
        }
    }

    Date newDate = Date(newDay, newMonth, newYear);
    return newDate;
}

bool Date::isEmpty() const {
    if (day == 0 && month == 0 && year == 0) {
        return true;
    }
    return false;
}

bool Date::operator==(const Date &inputDate) const {
    return this->getDate() == inputDate.getDate();
}

std::istream& operator>>(std::istream &is, Date &date) {
    int d, m, y = 0;
    char sep1, sep2;

    if (is >> d >> sep1 >> m >> sep2 >> y) {
        if (sep1 == SLASH && sep2 == SLASH) {
            date.setDate(d, m, y);
            return is;
        }
    }

    is.setstate(std::ios::failbit);
    return is;
}