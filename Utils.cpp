#include "Utils.h"
#include "Date.h"

using namespace std;

bool Utils::isValid(string &str) {
    for (auto it = str.cbegin(); it != str.cend(); it++)
        if (!isdigit(*it) && (it != str.cbegin() || *it != '-' || str.length() == 1))
            return false;

    return !str.empty();
}




Date Utils::parse(string sdate) {
    Date r;
    Date bad = Date(-1, -1, -1);
    int len = sdate.length();
    sdate.append("a");
    if (sdate.find_first_not_of("0123456789.") != len)
        return bad;
    sdate = sdate.substr(0, sdate.length() - 1);
    char *c_st = new char[sdate.length() + 1];
    strcpy_s(c_st, sdate.length() + 1, sdate.c_str());
    char *part, *posn;
    part = strtok_s(c_st, ".", &posn);
    int c = 0;
    while (part != NULL) {
        switch (c)
        {
            case 0:
                r.day = stoi(part);
                break;
            case 1:
                r.mon = stoi(part);
                break;
            case 2:
                r.year = stoi(part);
                break;
            default:
                break;
        }
        part = strtok_s(NULL, ".", &posn);
        c++;
    }
    delete c_st;
    delete part;
    posn = nullptr;
    if (c != 3)
        return bad;
    return r;
}
