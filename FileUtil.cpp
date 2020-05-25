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
    char name[50];
    char birth[15];
    int postup;
    char kaf[20];
    char group[15];
    char zachetka[15];
    Session sessions[9];
    int sessionsCout;
    int gender;
} typedef Student;


bool FileUtil::validateStudent(const char num[]){
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    while(!feof(file)){
        if(fread(&output, sizeof(struct Student), 1, file)){
            if(strcmp(output.zachetka, num) == 0){
                fclose(file);
                return false;
            }
        }
    }
    fclose(file);
    return true;
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
        printf_s("%s, %s, %d, %s, %s, %s \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
    }
    fclose(file);
}

void FileUtil::printMarks(Student output){
    int count = output.sessionsCout;
    int sess = 0;
    for(int i = 0; i < count; i++){
        sess++;
        cout << "������ #" + to_string(sess) << endl;
        int subjCount = output.sessions[i].count;
        for(int x = 0; x < subjCount; x++){
            cout << output.sessions[i].subj[x];
            cout << ": ";
            cout << output.sessions[i].marks[x] << endl;
        }
    }
}

bool FileUtil::genderCheck(int gender, Student student){
    return student.gender == gender || gender == 3;
}

bool FileUtil::calculate(int action, Student student){
    double first = 0, all = 0;
    int count = student.sessionsCout;
    switch (action) {
        case 1:{
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 3){
                        first++;
                    }
                    all++;
                }
            }
            cout << first/all << endl;
            return first/all < 0.25;
        }
        case 2:{
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 3 || student.sessions[i].marks[x] == 4){
                        first++;
                    }
                    all++;
                }
            }
            cout << first/all << endl;
            return first/all < 0.25;
        }
        case 3:{
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 5){
                        first++;
                    }
                    all++;
                }
            }
            return first/all < 0.25;
        }
        case 4:{
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 3 || student.sessions[i].marks[x] == 5){
                        first++;
                    }
                    all++;
                }
            }
            cout << first/all << endl;
            return first/all < 0.25;
        }
        case 5:{
            for(int i = 0; i < count; i++){
                int subjCount = student.sessions[i].count;
                for(int x = 0; x < subjCount; x++){
                    if(student.sessions[i].marks[x] == 4 || student.sessions[i].marks[x] == 5){
                        first++;
                    }
                    all++;
                }
            }
            return first/all < 0.25;
        }
        default:{
            cout << "���������� ������" << endl;
        }
    }
    return false;
}

void FileUtil::sorting(int action){
    bool found = false;
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
                found = true;
                cout << "��� | ���� �������� | ��� ����������� | ������� | ������ | ����� �������" << endl;
                printf_s("%s, %s, %d, %s, %s, %s \n", output.name, output.birth, output.postup, output.kaf, output.group, output.zachetka);
                FileUtil::printMarks(output);
            }
        }
    }
    if(!found){
        cout << "�������� �� �������!" << endl;
    }
    fclose(file);
}

void FileUtil::allStudentMarks(const char zach[]){
    FILE *file;
    Student output;
    file = fopen("person.dat", "r+");
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (strcmp(output.zachetka, zach) == 0) {
                printMarks(output);
            }
        }
    }
}

void FileUtil::studentAction(const char zach[], int action) {
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    bool found = false;
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (strcmp(output.zachetka, zach) == 0) {
                fclose(file);
                switch (action) {
                    case 1:{
                        FileUtil::recreateFileWithDelete(zach);
                        found = true;
                        //Utils::open();
                        break;
                    }
                    case 2:{
                        FileUtil::recreateFileWithEdit(zach);
                        found = true;
                        //Utils::open();
                        break;
                    }
                    case 3:{
                        FileUtil::allStudentMarks(zach);
                        found = true;
                        //Utils::open();
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
    if(!found){
        cout << "������� �� ������!" << endl;
    }
}

void FileUtil::recreateFileWithEdit(const char zach[]){
    remove("temp.dat");
    FILE *file = fopen("person.dat", "r+");
    FILE *temp = fopen("temp.dat", "a+t");
    int n = FileUtil::getStudentCount();
    Student output1;
    for (int i = 0; i < n; i++) {
        fread(&output1, sizeof(struct Student), 1, file);
        if(strcmp(output1.zachetka, zach) != 0){
            fwrite(&output1, sizeof(struct Student), 1, temp);
        }else{
            cout << "��� | ���� �������� | ��� ����������� | ������� | ������ | ����� �������" << endl;
            printf_s("%s, %s, %d, %s, %s, %s \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
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
                    while(!validateStudent(temp2.c_str())){
                        cout << "������ ����� ��� ���� � ����! ������� ����� ��� �������� 0 ����� ��������." << endl;
                        getline(cin, temp2);
                    }
                    strcpy_s(output1.zachetka, temp2.c_str());
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
                    int sess = 0;
                    for (int y = 0; y < x; y++) {
                        sess++;
                        cout << "������� ������ ��� ������ #" + to_string(sess) << endl;
                        string subj;
                        cout << "������� ���������� ��������� � ������ ������." << endl;
                        int count = Utils::validateInt(1, 10);
                        Session session;
                        session.count = count;
                        for (int num = 0; num < count; num++) {
                            cout << "������� �������." << endl;
                            getline(cin, subj);
                            char ff[100];
                            strcpy_s(ff, subj.c_str());
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
}

void FileUtil::recreateFileWithDelete(const char zach[]){
    remove("temp.dat");
    int n = FileUtil::getStudentCount();
    FILE *file = fopen("person.dat", "r+");
    FILE *temp = fopen("temp.dat", "a+t");
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, file);
        if(strcmp(output1.zachetka, zach) != 0){
            fwrite(&output1, sizeof(struct Student), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove("person.dat");
    file = fopen("person.dat", "a+t");
    temp = fopen("temp.dat", "r+");
    n--;
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, temp);
        if(output1.zachetka != zach){
            fwrite(&output1, sizeof(struct Student), 1, file);
        }
    }
    fclose(temp);
    fclose(file);
    remove("temp.dat");
    cout << "������� ������ �������." << endl;
}

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
        while(!validateStudent(temp2.c_str())){
            cout << "������ ����� ��� ���� � ����! ������� ����� ��� �������� 0 ����� ��������." << endl;
            getline(cin, temp2);
        }
        strcpy_s(stud.zachetka, temp2.c_str());
        cout << "������� ���. 1 - �, 2 - �" << endl;
        int gender = Utils::validateInt(1, 2);;
        stud.gender = gender;
        int x;
        cout << "������� ���������� ������" << endl;
        int str = Utils::validateInt(1, 9);
        stud.sessionsCout = str;
        x = str;
        int sess = 0;
        for (int y = 0; y < x; y++) {
            sess++;
            cout << "������� ������ ��� ������ #" + to_string(sess) << endl;
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
                stud.sessions[y] = session;
            }

        }
        cout << "������ �������� ������� ���������!" << endl;
        FILE *file;
        file = fopen("person.dat", "a+t");
        fwrite(&stud, sizeof(struct Student), 1, file);
        fclose(file);
    }




