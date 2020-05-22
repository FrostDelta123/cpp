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
        cout << "���� ����. ����� ������� ��������� ��������� ����." << endl;
        Utils::open();
    }
}

void Utils::open(){
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
        Utils::open();
    }
    if((stoi(n) > 5 || stoi(n) < 0)){
        cout << "������� ����� �� 0 �� 5" << endl;
        Utils::open();
    }
    switch(stoi(n)){
        //������, ���������.
        case 0: {
            exit(0);
        }
            //������, ���������.
        case 1:{
            FileUtil::enterStudent();
            Utils::open();
        }
        case 2:{
            Utils::checkFile();
            FileUtil::test();
            Utils::open();
        }
            //������, ���������.
        case 3:{
            Utils::checkFile();
            FileUtil::printAll();
            Utils::open();
        }
        case 4:{
            Utils::checkFile();
            Utils::open();
        }
        case 5:{
            Utils::checkFile();
            Utils::open();
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
