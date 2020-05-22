#include <iostream>
#include <Windows.h>
#include "Utils.h"

using namespace std;

int main () {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    while(true) Utils::open();
    return 0;
}

