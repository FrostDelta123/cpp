#include "Date.h"
#include "Utils.h"
#include <string>
using  namespace std;
Date::Date() {
    this->day = 0;
    this->mon = 0;
    this->year = 0;
}
Date::Date(int _day, int _mon, int _year) {
    this->day = _day;
    this->mon = _mon;
    this->year = _year;
}
int Date::isValid(int day, int mon, int year) {
    return ((day > 0) && (day <= 31) && (mon > 0) && (mon <= 12) && (year >= 0) && (year <= 9999));
}
bool Date::isValid(string sdate) {
    Date d = Utils::parse(sdate);
    return isValid(d);
}
bool Date::isValid(Date date) {
    return ((date.day > 0) && (date.day <= 31) && (date.mon > 0) && (date.mon <= 12) && (date.year >= 0) && (date.year <= 9999));
}