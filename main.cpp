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
        FILE* file;
        cout << "Файл не найден или пуст, создаём. Перед работой требуется заполнить файл." << endl;
        file = fopen("person.dat", "a+t");
        fclose(file);
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
        //Готово, корректно.
        case 0: {
            exit(0);
        }
        //Готово, корректно.
        case 1:{
            FileUtil::enterStudent();
            open();
        }
        case 2:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
        }
        //Готово, корректно.
        case 3:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
            FileUtil::printAll();
            open();
        }
        case 4:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
            open();
        }
        case 5:{
            if(FileUtil::isEmpty()){
                cout << "Файл пуст. Перед работой требуется заполнить файл." << endl;
                open();
            }
            open();
        }
    }
}
