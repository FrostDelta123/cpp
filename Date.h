#ifndef KURSACHNEW_DATE_H
#define KURSACHNEW_DATE_H
#include <string>

using namespace std;
class Date {
public:
    Date();

    int day = 0, mon = 0, year = 0;
    static int isValid(int, int, int);
    static bool isValid(string);
    static bool isValid(Date);
    Date(int, int, int);
};


#endif //KURSACHNEW_DATE_H
