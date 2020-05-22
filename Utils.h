#ifndef KURSACHNEW_UTILS_H
#define KURSACHNEW_UTILS_H


#include <string>
#include "Date.h"

using namespace std;

class Utils {
public:
    static bool isValid(string &);
    static Date parse(string);
    static void open();
    static void checkFile();
};


#endif //KURSACHNEW_UTILS_H
