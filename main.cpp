#include <iostream>
#include <Windows.h>
#include "FileUtil.h"
#include "Utils.h"
#include <string>

void open();

using namespace std;

int main () {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    while(true) open();
    return 0;
}

void open(){
    if(!FileUtil::checkFile()){
        cout << "Файл не найден или пуст, создаём. Перед работой требуется заполнить файл." << endl;
        fopen("person.dat", "a+t");
    }
    string n;
    cout << "Введите номер действия: " << endl;
    cout << "1. Добавить студентов." << endl;
    cout << "2. Удалить студента." << endl;
    cout << "3. Список всех студентов." << endl;
    cout << "4. Изменить информацию о студенте." << endl;
    cout << "5. Отсортировать." << endl;
    cout << "0. Выход." << endl;
    getline(cin, n);
    if(!Utils::isValid(n)){
        cout << "Введите число от 0 до 5" << endl;
        open();
    }
    if((stoi(n) > 5 || stoi(n) < 0)){
        cout << "Введите число от 0 до 5" << endl;
        open();
    }
    switch(stoi(n)){
        case 0: {
            exit(0);
        }
        case 1:{
            FileUtil::enterStudent();
            //FileUtil::test();
            open();
        }
        case 2:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
        }
        case 3:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
            //Доделать
            FileUtil::printAll();
        }
        case 4:{
            string date;
            getline(cin, date);
            cout << Date::isValid(date) << endl;
        }
        case 5:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
        }
    }
}
