#include "FileUtil.h"
#include "Date.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Session{
    char subj[100][200];
    int marks[10];
    int count;
} typedef Session;

struct Student{
    char name[40];
    char birth[15];
    int postup;
    char kaf[25];
    char group[10];
    //���������� � char
    int zachetka;
    Session sessions[9];
    int sessionsCout;
    int gender;
} typedef Student;


//����� ��������
int FileUtil::validateStudent(int num){
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    while(!feof(file)){
        if(fread(&output, sizeof(struct Student), 1, file)){
            if(output.zachetka == num){
                string temp;
                cout << "������ ����� ��� ���� � ����! ������� ����� ��� �������� 0 ����� ��������." << endl;
                getline(cin, temp);
                while(!Utils::isValid(temp)){
                    cout << "������ �����, ������� ����� ����� ��� �������� 0 ����� ��������." << endl;
                    getline(cin, temp);
                }
                fclose(file);
                FileUtil::validateStudent(stoi(temp));
            }
        }
    }
    fclose(file);
    return num;
}


int FileUtil::getStudentCount(){
    int i = 0;
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    while(!feof(file)){
        if(fread(&output, sizeof(struct Student), 1, file)){
            i++;
        }
    }
    fclose(file);
    cout << i << endl;
    return i;
}

bool FileUtil::isEmpty(){
    ifstream base("person.dat");
    if (base.is_open ()){
        base.seekg (0, ios::end);
        int size = base.tellg();
        base.seekg (0, ios::beg);

        if (size == 0){
            base.close();
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

void FileUtil::printAll() {
    FILE *file;
    file = fopen("person.dat", "r+");
    int n = FileUtil::getStudentCount();
    cout << "��� | ���� �������� | ��� ����������� | ������� | ������ | ����� �������" << endl;
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, file);
        printf_s("%s, %s, %d, %s, %s, %d \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
    }
    fclose(file);
}

void FileUtil::printMarks(Student output){
    int count = output.sessionsCout;
    for(int i = 0; i < count; i++){
        //����� ������
        cout << "������ # " << endl;
        int subjCount = output.sessions[i].count;
        for(int x = 0; x < subjCount; x++){
            cout << output.sessions[i].subj[x];
            cout << ": ";
            cout << output.sessions[i].marks[x] << endl;
        }
    }
    Utils::open();
}

bool FileUtil::genderCheck(int gender, Student student){
    return student.gender == gender || gender == 3;
}


//����� ��������, ��������� � ���������.
bool FileUtil::calculate(int action, Student student){
    double first = 0, second = 0, all = 0;
    switch (action) {
        case 1:{
            int count = student.sessionsCout;
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 3){
                        first++;
                    }
                    all++;
                }
            }
            return first/all < 0.25;
        }
        case 2:{

        }
        case 3:{

        }
        case 4:{

        }
        case 5:{

        }
        default:{
            cout << "���������� ������" << endl;
            Utils::open();
        }
    }
}

void FileUtil::sorting(int action){
    FILE *file;
    Student output;
    file = fopen("person.dat", "r+");
    cout << "������� ��� ���������� �� ����." << endl;
    cout << "1. �������." << endl;
    cout << "2. �������." << endl;
    cout << "3. �����." << endl;
    int code = Utils::validateInt(1, 3);
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (FileUtil::calculate(action, output) && FileUtil::genderCheck(code, output)) {
                cout << "��� | ���� �������� | ��� ����������� | ������� | ������ | ����� �������" << endl;
                printf_s("%s, %s, %d, %s, %s, %d \n", output.name, output.birth, output.postup, output.kaf, output.group, output.zachetka);
                FileUtil::printMarks(output);
            }
        }
    }
    Utils::open();
}

void FileUtil::allStudentMarks(int zach){
    FILE *file;
    Student output;
    file = fopen("person.dat", "r+");
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (output.zachetka == zach) {
                printMarks(output);
            }
        }
    }
}

void FileUtil::studentAction(int zach, int action) {
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (output.zachetka == zach) {
                fclose(file);
                switch (action) {
                    case 1:{
                        FileUtil::recreateFileWithDelete(zach);
                        break;
                    }
                    case 2:{
                        FileUtil::recreateFileWithEdit(zach);
                        break;
                    }
                    case 3:{
                        FileUtil::allStudentMarks(zach);
                        break;
                    }
                    default: {
                        cout << "���������� ������" << endl;
                        break;
                    }
                }
            }
        }
    }
    cout << "������� �� ������!" << endl;
    Utils::open();
}

void FileUtil::recreateFileWithEdit(int zach){
    remove("temp.dat");
    FILE *file = fopen("person.dat", "r+");
    FILE *temp = fopen("temp.dat", "a+t");
    int n = FileUtil::getStudentCount();
    Student output1;
    for (int i = 0; i < n; i++) {
        fread(&output1, sizeof(struct Student), 1, file);
        if(output1.zachetka != zach){
            fwrite(&output1, sizeof(struct Student), 1, temp);
        }else{
            cout << "��� | ���� �������� | ��� ����������� | ������� | ������ | ����� �������" << endl;
            printf_s("%s, %s, %d, %s, %s, %d \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
            cout << "������� ����� ��������: " << endl;
            cout << "1. �������� ���." << endl;
            cout << "2. �������� ���� ��������" << endl;
            cout << "3. �������� ��� �����������." << endl;
            cout << "4. �������� �������." << endl;
            cout << "5. �������� ������." << endl;
            cout << "6. �������� ����� �������." << endl;
            cout << "7. �������� ���." << endl;
            cout << "8. �������� ���������� � �������." << endl;
            int action = Utils::validateInt(1, 8);
            string fa, name, ot, fio, date, fak, kaf, group;
            switch (action) {
                case 1: {
                    cout << "������� �������." << endl;
                    getline(cin, fa);
                    fio.append(fa);
                    cout << "������� ���." << endl;
                    getline(cin, name);
                    fio.append(" " + name);
                    cout << "������� ��������." << endl;
                    getline(cin, ot);
                    fio.append(" " + ot);
                    strcpy_s(output1.name, fio.c_str());
                    cout << "��� ��������" << endl;
                    break;
                }
                case 2:{
                    cout << "������� ���� �������� � ������� ��.��.����" << endl;
                    getline(cin, date);
                    while (!Date::isValid(date)) {
                        cout << "���� ������� �����������! ��������� ����." << endl;
                        getline(cin, date);
                    }
                    strcpy_s(output1.birth, date.c_str());
                    cout << "���� �������� ��������." << endl;
                    break;
                }
                case 3:{
                    cout << "������� ��� ����������� � �����������." << endl;
                    string temp1;
                    getline(cin, temp1);
                    while (!Utils::isValid(temp1)) {
                        cout << "��� ����� �����������! ��������� ����." << endl;
                        getline(cin, temp1);
                    }
                    output1.postup = stoi(temp1);
                    cout << "��� ����������� �������." << endl;
                    break;
                }
                case 4:{
                    cout << "������� ���������." << endl;
                    getline(cin, fak);
                    cout << "������� �������." << endl;
                    getline(cin, kaf);
                    fak.append(" " + kaf);
                    strcpy_s(output1.kaf, fak.c_str());
                    cout << "��������� � ������� ��������." << endl;
                    break;
                }
                case 5:{
                    cout << "������� ������." << endl;
                    getline(cin, group);
                    strcpy_s(output1.group, group.c_str());
                    cout << "������ ��������" << endl;
                    break;
                }
                case 6:{
                    cout << "������� ����� �������." << endl;
                    string temp2;
                    getline(cin, temp2);
                    while (!Utils::isValid(temp2)) {
                        cout << "����� ����� �����������! ��������� ����." << endl;
                        getline(cin, temp2);
                    }
                    output1.zachetka = FileUtil::validateStudent(stoi(temp2));
                    cout << "����� ������� �������" << endl;
                    zach = output1.zachetka;
                    break;
                }
                case 7:{
                    cout << "������� ���. 1 - �, 2 - �" << endl;
                    int gender = Utils::validateInt(1, 2);
                    output1.gender = gender;
                    cout << "��� �������." << endl;
                    break;
                }
                case 8:{
                    int x;
                    int str = Utils::validateInt(1, 9);
                    cout << "������� ���������� ������" << endl;
                    output1.sessionsCout = str;
                    x = str;
                    for (int y = 0; y < x; y++) {
                        //���� �����
                        cout << "������� ������ ��� ������ #" + to_string(y) << endl;
                        string subj;
                        cout << "������� ���������� ��������� � ������ ������." << endl;
                        int count = Utils::validateInt(1, 10);
                        Session session;
                        session.count = count;
                        for (int num = 0; num < count; num++) {
                            cout << "������� �������." << endl;
                            getline(cin, subj);
                            char ff[100];
                            strcpy(ff, subj.c_str());
                            strcpy_s(session.subj[num], ff);
                            cout << "������� ������ �� �������� " + subj << endl;
                            int tem = Utils::validateInt(2, 5);
                            session.marks[num] = tem;
                            output1.sessions[y] = session;
                        }
                    }
                    cout << "���������� � ������� ��������." << endl;
                    break;
                }
            }
            fwrite(&output1, sizeof(struct Student), 1, temp);
        }

    }
    fclose(file);
    fclose(temp);
    remove("person.dat");
    FILE *file2 = fopen("person.dat", "a+t");
    FILE *temp2 = fopen("temp.dat", "a+t");
    for (int i = 0; i < n; i++) {
        Student student;
        fread(&student, sizeof(struct Student), 1, temp2);
        fwrite(&student, sizeof(struct Student), 1, file2);
    }
    fclose(temp2);
    fclose(file2);
    remove("temp.dat");
    Utils::open();
}

void FileUtil::recreateFileWithDelete(int zach){
    remove("temp.dat");
    int n = FileUtil::getStudentCount();
    FILE *file = fopen("person.dat", "r+");
    FILE *temp = fopen("temp.dat", "a+t");
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, file);
        if(output1.zachetka != zach){
            fwrite(&output1, sizeof(struct Student), 1, temp);
        }
    }
    fclose(file);
    remove("person.dat");
    file = fopen("person.dat", "a+t");
    n--;
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, temp);
        if(output1.zachetka != zach){
            fwrite(&output1, sizeof(struct Student), 1, file);
        }
    }
    cout << "������� ������� �����!" << endl;
    fclose(temp);
    fclose(file);
    remove("temp.dat");
    Utils::open();
}


//TODO ��������� �����. �����
    void FileUtil::enterStudent() {
        Student stud;
        string fa, name, ot, fio, date, fak, kaf, group;
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
        while (!Date::isValid(date)) {
            cout << "���� ������� �����������! ��������� ����." << endl;
            getline(cin, date);
        }
        strcpy_s(stud.birth, date.c_str());
        cout << "������� ��� ����������� � �����������." << endl;
        string temp;
        getline(cin, temp);
        while (!Utils::isValid(temp)) {
            cout << "��� ����� �����������! ��������� ����." << endl;
            getline(cin, temp);
        }
        stud.postup = stoi(temp);
        cout << "������� ���������." << endl;
        getline(cin, fak);
        cout << "������� �������." << endl;
        getline(cin, kaf);
        fak.append(" " + kaf);
        strcpy_s(stud.kaf, fak.c_str());
        cout << "������� ������." << endl;
        getline(cin, group);
        strcpy_s(stud.group, group.c_str());
        cout << "������� ����� �������." << endl;
        string temp2;
        getline(cin, temp2);
        while (!Utils::isValid(temp2)) {
            cout << "����� ����� �����������! ��������� ����." << endl;
            getline(cin, temp2);
        }
        stud.zachetka = FileUtil::validateStudent(stoi(temp2));
        cout << "������� ���. 1 - �, 2 - �" << endl;
        int gender = Utils::validateInt(1, 2);;
        stud.gender = gender;
        int x;
        cout << "������� ���������� ������" << endl;
        int str = Utils::validateInt(1, 9);
        stud.sessionsCout = str;
        x = str;
        for (int y = 0; y < x; y++) {
            //����� ������ ���
            cout << "������� ������ ��� ������ #" + to_string(y) << endl;
            string subj;
            cout << "������� ���������� ��������� � ������ ������." << endl;
            int count = Utils::validateInt(1, 10);
            Session session;
            session.count = count;
            for (int num = 0; num < count; num++) {
                cout << "������� �������." << endl;
                getline(cin, subj);
                char ff[100];
                strcpy(ff, subj.c_str());
                strcpy_s(session.subj[num], ff);
                cout << "������� ������ �� �������� " + subj << endl;
                int tem = Utils::validateInt(2, 5);
                cout << to_string(num) + " " + to_string(y) << endl;
                session.marks[num] = tem;
                stud.sessions[y] = session;
            }

        }
        cout << "������ �������� ������� ���������!" << endl;
        FILE *file;
        file = fopen("person.dat", "a+t");
        fwrite(&stud, sizeof(struct Student), 1, file);
        fclose(file);
    }




