#include <sstream>
#include <string>
#include "Date.h"

Date::Date() {
    year_ = 1947;
    month_ = 1;
    day_ = 1;
    hour_ = 0;
    minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}

int Date::getYear(void) const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}
int Date::getMonth(void) const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.year_ % 100) {
      if (date.year_ % 400)
        days[2] = 29;
    } else if (date.year_ % 4) {
      days[2] = 29;
      }

    if (date.year_ < 1000 || date.year_ > 9999 || date.month_ < 1 ||
    date.month_ > 12 || date.day_ < 1 || date.day_ > days[date.month_] ||
    date.hour_ < 0 || date.hour_ > 23 ||date.minute_ < 0 || date.minute_ > 59)
    return false;
    return true;
}

Date Date::stringToDate(std::string dateString) {
    int year = 0, month, day, hour, minute, tem;
    for (int i = 0; i < 4; i++)
      year = year * 10 + dateString[i] - '0';
    month = (dateString[5] - '0') * 10 + dateString[6] - '0';
    day = (dateString[8] - '0') * 10 + dateString[9] - '0';
    hour = (dateString[11] - '0') * 10 + dateString[12] - '0';
    minute = (dateString[14] - '0') * 10 + dateString[15] - '0';
    Date ret(year, month, day, hour, minute);
    return ret;
}

std::string Date::dateToString(Date date) {
    std::stringstream ss;
    std::string ret = "";
    ss << date.year_ << '-';
    if (date.month_ < 10)
    ss << '0';
    ss << date.month_ << '-';
    if (date.day_ < 10)
    ss << '0';
    ss << date.day_ << '/';
    if (date.hour_ < 10)
    ss << '0';
    ss << date.hour_ << ':';
    if (date.minute_
    < 10)
    ss << '0';
    ss << date.minute_;
    ss >> ret;
    return ret;
}
Date& Date::operator=(const Date& date) {
    this->year_ = date.year_;
    this->month_ = date.month_;
    this->day_ = date.day_;
    this->hour_ = date.hour_;
    this->minute_ = date.minute_;
    return *this;
}
bool Date::operator==(const Date& date) const {
    return ((*this) <= date && (*this) >= date);
}

bool Date::operator>(const Date& date) const {
    if (this->year_ > date.year_)
      return true;
    else if (this->year_ < date.year_)
      return false;
    if (this->month_ > date.month_)
      return true;
    else if (this->month_ < date.month_)
      return false;
    if (this->day_ > date.day_)
      return true;
    else if (this->day_ < date.day_)
      return false;
    if (this->hour_ > date.hour_)
      return true;
    else if (this->hour_ < date.hour_)
      return false;
    if (this->minute_ > date.minute_)
      return true;
    else if (this->minute_ < date.minute_)
      return false;
    return false;
}

bool Date::operator<(const Date& date) const {
    if (this->year_ < date.year_)
      return true;
    else if (this->year_ > date.year_)
      return false;
    if (this->month_ < date.month_)
      return true;
    else if (this->month_ > date.month_)
      return false;
    if (this->day_ < date.day_)
      return true;
    else if (this->day_ > date.day_)
      return false;
    if (this->hour_ < date.hour_)
      return true;
    else if (this->hour_ > date.hour_)
      return false;
    if (this->minute_ < date.minute_)
      return true;
    else if (this->minute_ > date.minute_)
      return false;
    return false;
}

bool Date::operator>=(const Date& date) const {
    return (*this) < date;
}

bool Date::operator<=(const Date& date) const {
    return (*this) > date;
}
