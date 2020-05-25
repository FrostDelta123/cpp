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
    cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
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
        cout << "Сессия #" + to_string(sess) << endl;
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
            cout << "Магическая ошибка" << endl;
        }
    }
    return false;
}

void FileUtil::sorting(int action){
    bool found = false;
    FILE *file;
    Student output;
    file = fopen("person.dat", "r+");
    cout << "Введите код сортировки по полу." << endl;
    cout << "1. Мужской." << endl;
    cout << "2. Женский." << endl;
    cout << "3. Любой." << endl;
    int code = Utils::validateInt(1, 3);
    while (!feof(file)) {
        if (fread(&output, sizeof(struct Student), 1, file)) {
            if (FileUtil::calculate(action, output) && FileUtil::genderCheck(code, output)) {
                found = true;
                cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
                printf_s("%s, %s, %d, %s, %s, %s \n", output.name, output.birth, output.postup, output.kaf, output.group, output.zachetka);
                FileUtil::printMarks(output);
            }
        }
    }
    if(!found){
        cout << "Студенты не найдены!" << endl;
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
                        cout << "Магическая ошибка" << endl;
                        break;
                    }
                }
            }
        }
    }
    if(!found){
        cout << "Студент не найден!" << endl;
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
            cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
            printf_s("%s, %s, %d, %s, %s, %s \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
            cout << "Введите номер действия: " << endl;
            cout << "1. Изменить ФИО." << endl;
            cout << "2. Изменить дату рождения" << endl;
            cout << "3. Изменить год поступления." << endl;
            cout << "4. Изменить кафедру." << endl;
            cout << "5. Изменить группу." << endl;
            cout << "6. Изменить номер зачётки." << endl;
            cout << "7. Изменить пол." << endl;
            cout << "8. Изменить информацию о сессиях." << endl;
            int action = Utils::validateInt(1, 8);
            string fa, name, ot, fio, date, fak, kaf, group;
            switch (action) {
                case 1: {
                    cout << "Введите Фамилию." << endl;
                    getline(cin, fa);
                    fio.append(fa);
                    cout << "Введите Имя." << endl;
                    getline(cin, name);
                    fio.append(" " + name);
                    cout << "Введите Отчество." << endl;
                    getline(cin, ot);
                    fio.append(" " + ot);
                    strcpy_s(output1.name, fio.c_str());
                    cout << "ФИО изменено" << endl;
                    break;
                }
                case 2:{
                    cout << "Введите дату рождения в формате ДД.ММ.ГГГГ" << endl;
                    getline(cin, date);
                    while (!Date::isValid(date)) {
                        cout << "Дата введена некорректно! Повторите ввод." << endl;
                        getline(cin, date);
                    }
                    strcpy_s(output1.birth, date.c_str());
                    cout << "Дата рождения изменена." << endl;
                    break;
                }
                case 3:{
                    cout << "Введите год постепления в университет." << endl;
                    string temp1;
                    getline(cin, temp1);
                    while (!Utils::isValid(temp1)) {
                        cout << "Год введён некорректно! Повторите ввод." << endl;
                        getline(cin, temp1);
                    }
                    output1.postup = stoi(temp1);
                    cout << "Год поступления изменен." << endl;
                    break;
                }
                case 4:{
                    cout << "Введите факультет." << endl;
                    getline(cin, fak);
                    cout << "Введите кафедру." << endl;
                    getline(cin, kaf);
                    fak.append(" " + kaf);
                    strcpy_s(output1.kaf, fak.c_str());
                    cout << "Факультет и кафедра изменены." << endl;
                    break;
                }
                case 5:{
                    cout << "Введите группу." << endl;
                    getline(cin, group);
                    strcpy_s(output1.group, group.c_str());
                    cout << "Группа изменена" << endl;
                    break;
                }
                case 6:{
                    cout << "Введите номер зачётки." << endl;
                    string temp2;
                    getline(cin, temp2);
                    while(!validateStudent(temp2.c_str())){
                        cout << "Данный номер уже есть в базе! Введите новый или напишите 0 чтобы прервать." << endl;
                        getline(cin, temp2);
                    }
                    strcpy_s(output1.zachetka, temp2.c_str());
                    cout << "Номер зачётки изменен" << endl;
                    zach = output1.zachetka;
                    break;
                }
                case 7:{
                    cout << "Введите пол. 1 - М, 2 - Ж" << endl;
                    int gender = Utils::validateInt(1, 2);
                    output1.gender = gender;
                    cout << "Пол изменен." << endl;
                    break;
                }
                case 8:{
                    int x;
                    int str = Utils::validateInt(1, 9);
                    cout << "Введите количество сессий" << endl;
                    output1.sessionsCout = str;
                    x = str;
                    int sess = 0;
                    for (int y = 0; y < x; y++) {
                        sess++;
                        cout << "Введите данные для сессии #" + to_string(sess) << endl;
                        string subj;
                        cout << "Введите количество предметов в данной сессии." << endl;
                        int count = Utils::validateInt(1, 10);
                        Session session;
                        session.count = count;
                        for (int num = 0; num < count; num++) {
                            cout << "Введите предмет." << endl;
                            getline(cin, subj);
                            char ff[100];
                            strcpy_s(ff, subj.c_str());
                            strcpy_s(session.subj[num], ff);
                            cout << "Введите оценку по предмету " + subj << endl;
                            int tem = Utils::validateInt(2, 5);
                            session.marks[num] = tem;
                            output1.sessions[y] = session;
                        }
                    }
                    cout << "Информация о сессиях изменена." << endl;
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
    cout << "Студент удален успешно." << endl;
}

    void FileUtil::enterStudent() {
        Student stud;
        string fa, name, ot, fio, date, fak, kaf, group;
        cout << "Введите Фамилию." << endl;
        getline(cin, fa);
        fio.append(fa);
        cout << "Введите Имя." << endl;
        getline(cin, name);
        fio.append(" " + name);
        cout << "Введите Отчество." << endl;
        getline(cin, ot);
        fio.append(" " + ot);
        strcpy_s(stud.name, fio.c_str());
        cout << "Введите дату рождения в формате ДД.ММ.ГГГГ" << endl;
        getline(cin, date);
        while (!Date::isValid(date)) {
            cout << "Дата введена некорректно! Повторите ввод." << endl;
            getline(cin, date);
        }
        strcpy_s(stud.birth, date.c_str());
        cout << "Введите год постепления в университет." << endl;
        string temp;
        getline(cin, temp);
        while (!Utils::isValid(temp)) {
            cout << "Год введён некорректно! Повторите ввод." << endl;
            getline(cin, temp);
        }
        stud.postup = stoi(temp);
        cout << "Введите факультет." << endl;
        getline(cin, fak);
        cout << "Введите кафедру." << endl;
        getline(cin, kaf);
        fak.append(" " + kaf);
        strcpy_s(stud.kaf, fak.c_str());
        cout << "Введите группу." << endl;
        getline(cin, group);
        strcpy_s(stud.group, group.c_str());
        cout << "Введите номер зачётки." << endl;
        string temp2;
        getline(cin, temp2);
        while(!validateStudent(temp2.c_str())){
            cout << "Данный номер уже есть в базе! Введите новый или напишите 0 чтобы прервать." << endl;
            getline(cin, temp2);
        }
        strcpy_s(stud.zachetka, temp2.c_str());
        cout << "Введите пол. 1 - М, 2 - Ж" << endl;
        int gender = Utils::validateInt(1, 2);;
        stud.gender = gender;
        int x;
        cout << "Введите количество сессий" << endl;
        int str = Utils::validateInt(1, 9);
        stud.sessionsCout = str;
        x = str;
        int sess = 0;
        for (int y = 0; y < x; y++) {
            sess++;
            cout << "Введите данные для сессии #" + to_string(sess) << endl;
            string subj;
            cout << "Введите количество предметов в данной сессии." << endl;
            int count = Utils::validateInt(1, 10);
            Session session;
            session.count = count;
            for (int num = 0; num < count; num++) {
                cout << "Введите предмет." << endl;
                getline(cin, subj);
                char ff[100];
                strcpy(ff, subj.c_str());
                strcpy_s(session.subj[num], ff);
                cout << "Введите оценку по предмету " + subj << endl;
                int tem = Utils::validateInt(2, 5);
                session.marks[num] = tem;
                stud.sessions[y] = session;
            }

        }
        cout << "Данные студента успешно сохранены!" << endl;
        FILE *file;
        file = fopen("person.dat", "a+t");
        fwrite(&stud, sizeof(struct Student), 1, file);
        fclose(file);
    }




