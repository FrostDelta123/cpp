#include "Utils.h"
#include "FileUtil.h"
#include "iostream"
using namespace std;

bool Utils::isValid(string &str) {
    for (auto it = str.cbegin(); it != str.cend(); it++)
        if (!isdigit(*it) && (it != str.cbegin() || *it != '-' || str.length() == 1))
            return false;

    return !str.empty();
}

void Utils::checkFile(){
    if(FileUtil::isEmpty()){
        cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
        //Utils::open();
    }
}

int Utils::validateInt(int min, int max){
    string tempStr;
    cout << "Введите число от " + to_string(min) + " до " + to_string(max) << endl;
    while(true) {
        getline(cin, tempStr);
        if(isValid(tempStr)){
            if(stoi(tempStr) >= min && stoi(tempStr) <= max) {
                return stoi(tempStr);
            }
        }
        cout << "Вы ввели неверное число, повторите ввод" << endl;
    }
}



void Utils::open(){
    if(!FileUtil::checkFile()){
        FILE* file;
        cout << "Файл не найден или пуст, создаём. Перед работой требуется заполнить файл." << endl;
        file = fopen("person.dat", "a+t");
        fclose(file);
    }
    cout << "Введите номер действия: " << endl;
    cout << "1. Добавить студентов." << endl;
    cout << "2. Удалить студента." << endl;
    cout << "3. Список всех студентов." << endl;
    cout << "4. Изменить информацию о студенте." << endl;
    cout << "5. Отсортировать." << endl;
    cout << "6. Вывести все оценки студента." << endl;
    cout << "0. Выход." << endl;

    int n = validateInt(0, 6);
    switch(n){
        case 0: {
            exit(0);
        }
        case 1:{
            FileUtil::enterStudent();
            break;
            //Utils::open();
        }
        case 2:{
            Utils::checkFile();
            string zach;
            cout << "Введите номер зачётки для удаления." << endl;
            getline(cin, zach);
            FileUtil::studentAction(zach.c_str(), 1);
            break;
            //Utils::open();
        }
        case 3:{
            Utils::checkFile();
            FileUtil::printAll();
            break;
            //Utils::open();
        }
        case 4:{
            Utils::checkFile();
            string zach;
            cout << "Введите номер зачётки для внесения правок." << endl;
            getline(cin, zach);
            FileUtil::studentAction(zach.c_str(), 2);
            break;
            //Utils::open();
        }
        //Готово, корректно.
        case 5:{
            Utils::checkFile();
            cout << "Введите номер действия." << endl;
            cout << "Отсортировать студентов у которых за все время обучения не более 25% " << endl;
            cout << "1. Оценок 3" << endl;
            cout << "2. Оценок 3 и 4" << endl;
            cout << "3. Оценок 5" << endl;
            cout << "4. Оценок 3 и 5" << endl;
            cout << "5. Оценок 4 и 5" << endl;
            int action = validateInt(1, 5);
            FileUtil::sorting(action);
            break;
            //Utils::open();
        }
        case 6: {
            Utils::checkFile();
            string zach;
            cout << "Введите номер зачётки." << endl;
            getline(cin, zach);
            FileUtil::studentAction(zach.c_str(), 3);
            break;
            //Utils::open();
        }
        default:{
            cout << "Магическая ошибка" << endl;
            //Utils::open();
        }
    }
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
    while (part != nullptr) {
        switch (c){
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
        part = strtok_s(nullptr, ".", &posn);
        c++;
    }
    delete[] c_st;
    delete part;
    posn = nullptr;
    if (c != 3)
        return bad;
    return r;
}
