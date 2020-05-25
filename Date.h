#ifndef KURSACHNEW_DATE_H
#define KURSACHNEW_DATE_H
#include <string>

using namespace std;
class Date {
public:
    Date(); //Конструктор класса
    int day = 0, mon = 0, year = 0; //Стандартные значения
    static int isValid(int, int, int); // Проверка даты на валидность. День, месяц, год
    static bool isValid(string);// Проверка даты на валидность. Строка DD.MM.YYYY
    static bool isValid(Date);// Проверка даты на валидность. Дата.
    Date(int, int, int); //Конструктор класса, принимающий на вход день, месяц и год
};


#endif
