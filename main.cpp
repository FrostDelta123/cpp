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
        cout << "���� �� ������ ��� ����, ������. ����� ������� ��������� ��������� ����." << endl;
        file = fopen("person.dat", "a+t");
        fclose(file);
    }
    string n;
    cout << "������� ����� ��������: " << endl;
    cout << "1. �������� ���������." << endl;
    cout << "2. ������� ��������." << endl;
    cout << "3. ������ ���� ���������." << endl;
    cout << "4. �������� ���������� � ��������." << endl;
    cout << "5. �������������." << endl;
    cout << "0. �����." << endl;
    getline(cin, n);
    if(!Utils::isValid(n)){
        cout << "������� ����� �� 0 �� 5" << endl;
        open();
    }
    if((stoi(n) > 5 || stoi(n) < 0)){
        cout << "������� ����� �� 0 �� 5" << endl;
        open();
    }
    switch(stoi(n)){
        //������, ���������.
        case 0: {
            exit(0);
        }
        //������, ���������.
        case 1:{
            FileUtil::enterStudent();
            open();
        }
        case 2:{
            if(FileUtil::isEmpty()){
                cout << "���� ����. ����� ������� ��������� ��������� ����." << endl;
                open();
            }
        }
        //������, ���������.
        case 3:{
            if(FileUtil::isEmpty()){
                cout << "���� ����. ����� ������� ��������� ��������� ����." << endl;
                open();
            }
            FileUtil::printAll();
            open();
        }
        case 4:{
            if(FileUtil::isEmpty()){
                cout << "���� ����. ����� ������� ��������� ��������� ����." << endl;
                open();
            }
            open();
        }
        case 5:{
            if(FileUtil::isEmpty()){
                cout << "���� ����. ����� ������� ��������� ��������� ����." << endl;
                open();
            }
            open();
        }
    }
}
