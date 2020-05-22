#include "FileUtil.h"
#include "Date.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

struct Session{
    char subj[80][100];
    int marks[10];
} typedef Session;

struct student{
    //char name[40];
    //char birth[15];
    //int postup;
    //char kaf[25];
    //char group[10];
    //int zachetka;
    //����� ����, test - ��������� ������ � �������� � ����������
    Session sessions[9];
    //int gender;
} typedef student;




//�� �������� ��� ����, ���������� � 0
int FileUtil::getStudentCount(){
    char *str = new char [1024];
    int i=0;
    ifstream base("person.dat");
    while (!base.eof()){
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete str;
    cout << i << endl;
    return i;
}

bool FileUtil::isEmpty(){
    ifstream base("person.dat");
    if (base.is_open ()){
        base.seekg (0, ios::end);
        int size = base.tellg ();
        base.seekg (0, ios::beg);

        if (size == 0){
            base.close ( );
            return true;
        }
    }
    return false;
}

bool FileUtil::checkFile() {
    ifstream file;
    file.open("person.dat");
    return !!file;
}

void FileUtil::printAll(){
    FILE *file;
    file = fopen("person.dat", "r+");
    int n = FileUtil::getStudentCount();
    for(int i = 0; i < n; i++) {
        struct student output1;
        fread(&output1, sizeof(struct student), 1, file);
        //����� �����.
        //printf("%s, %s, %d, {%d %d ...}\n", output1.name, output1.birth, output1.age, output1.tabel[0], output1.tabel[1]);
    }
}



//TODO �������� �������� ��������� ����� (���� �� ���� ����� ������ �� �����/���� ���� � ��. ��, ���� �� ���)
void FileUtil::enterStudent(){
    struct student stud;
    /*string fa, name, ot, fio, date, kaf, group;
    cout << "������� �������." << endl;
    getline(cin, fa);
    fio.append(fa);
    cout << "������� ���." << endl;
    getline(cin, name);
    fio.append(" " + name);
    cout << "������� ��������." << endl;
    getline(cin, ot);
    fio.append(" " + ot);
    strcpy_s(stud.name, fio.c_str());
    cout << "������� ���� �������� � ������� ��.��.����" << endl;
    getline(cin, date);
    while (!Date::isValid(date)){
        cout << "���� ������� �����������! ��������� ����." << endl;
        getline(cin, date);
    }
    strcpy_s(stud.birth, date.c_str());
    cout << "������� ��� ����������� � �����������." << endl;
    string temp;
    getline(cin, temp);
    while(!Utils::isValid(temp)){
        cout << "��� ����� �����������! ��������� ����." << endl;
        getline(cin, temp);
    }
    stud.postup = stoi(temp);
    cout << "������� ���������, �������." << endl;
    getline(cin, kaf);
    strcpy_s(stud.kaf, kaf.c_str());

    //������� ����������� �������� ��� ������
    cout << "������� ������." << endl;
    getline(cin, group);
    strcpy_s(stud.group, group.c_str());
    cout << "������� ����� �������." << endl;
    string temp2;
    getline(cin, temp2);
    while(!Utils::isValid(temp2)){
        cout << "����� ����� �����������! ��������� ����." << endl;
        getline(cin, temp2);
    }
    stud.zachetka = stoi(temp2);
         */
    int x;
    string str;
    cout << "������� ���������� ������" << endl;
    getline(cin, str);
    while(!Utils::isValid(str)){
        cout << "������� ����� �� 1 �� 9.";
        getline(cin, str);
    }
    while(stoi(str) <= 0 || stoi(str) > 9){
        cout << "������� ����� �� 1 �� 9.";
        getline(cin, str);
    }
    x = stoi(str);

    //������ �������-�����.
    for(int y = 0; y < x; y++){
        //��������� ����� ������
        cout << "������� ������ ��� ������ #" + to_string(y) << endl;
        string subj, tem;
        string count;
        cout << "������� ���������� ��������� � ������ ������." << endl;
        getline(cin, count);
        while(!Utils::isValid(count)) {
            cout << "������� ����� �� 1 �� 10" << endl;
            getline(cin, count);
        }
        while(stoi(count) < 1 || stoi(count) > 10){
            cout << "������� ����� �� 1 �� 10" << endl;
            getline(cin, count);
        }
        for(int num = 0; num < stoi(count); num++) {
            struct Session session;
            cout << "������� �������." << endl;
            getline(cin, subj);
            char ff[100];
            strcpy_s(ff, subj.c_str());
            strcpy_s(session.subj[num], ff);

            cout << "������� ������ �� �������� " + subj << endl;
            getline(cin, tem);
            while (!Utils::isValid(tem)) {
                cout << "������ ������� �������, ���������." << endl;
                getline(cin, tem);
            }
            while (stoi(tem) < 2 || stoi(tem) > 5) {
                cout << "������ ������� �������, ���������. ������� ����� �� 2 �� 5." << endl;
                getline(cin, tem);
            }
            session.marks[num] = stoi(tem);
            stud.sessions[x] = session;
            cout << stud.sessions[0].subj[0] << endl;
            cout << stud.sessions[0].marks[0] << endl;
        }

    }
    cout << "top" << endl;
    FILE* file;
    file = fopen ("person.dat", "a");
    fwrite(&stud, sizeof(struct student),1, file);
    fclose(file);
}


void FileUtil::test() {
    FILE *file2;
    file2 = fopen("person.dat", "r+");

    //������� ���������� ����
    int n = 1;
    for(int i = 0; i < n; i++) {
        student output1;
        fread(&output1, sizeof(struct student), 1, file2);
        cout << output1.sessions[0].subj[0] << endl;
    }
    fclose(file2);
 /*   FILE *file;
    file = fopen ("person.dat", "a+t");
    if (file == NULL) {
        fprintf(stderr, "���-�� �� ���, �������������!\n");
        exit (1);
    }
    struct student input1 = {"First", "Tenebrius", 15, {1, 2, 3}};
    struct student input2 = {"Ivan", "Ivanov", 10, {7, 8}};
    char u[10] = "pizda";

    int studentLen = 2;
    fwrite(&studentLen, sizeof(int), 1, file);
    fwrite (&input1, sizeof(struct student), 1, file);
    fwrite (&input2, sizeof(struct student), 1, file);
    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else printf("error writing file !\n");
    fclose (file);
    FILE *file2;
    file2 = fopen ("person.dat", "r+");

    int n;
    fread(&n, sizeof(int), 1, file2);
    for(int i = 0; i < n; i++) {
        struct student output1;
        fread(&output1, sizeof(struct student), 1, file2);
        printf("%s, %s, %d, {%d %d ...}\n", output1.name, output1.birth, output1.age, output1.tabel[0], output1.tabel[1]);

    }*/
    
}




