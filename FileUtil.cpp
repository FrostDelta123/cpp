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
    //Переделать в char
    int zachetka;
    Session sessions[9];
    int sessionsCout;
    int gender;
} typedef Student;


//Криво работает
int FileUtil::validateStudent(int num){
    FILE *file;
    file = fopen("person.dat", "r+");
    Student output;
    while(!feof(file)){
        if(fread(&output, sizeof(struct Student), 1, file)){
            if(output.zachetka == num){
                string temp;
                cout << "Данный номер уже есть в базе! Введите новый или напишите 0 чтобы прервать." << endl;
                getline(cin, temp);
                while(!Utils::isValid(temp)){
                    cout << "Ошибка ввода, введите новый номер или напишите 0 чтобы прервать." << endl;
                    getline(cin, temp);
                }
                if(stoi(temp) == 0){
                    fclose(file);
                    Utils::open();
                }
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
    cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, file);
        printf_s("%s, %s, %d, %s, %s, %d \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
    }
    fclose(file);
}

//почти работает, исправить
void FileUtil::printMarks(Student output){
    int count = output.sessionsCout;
    for(int i = 0; i < count; i++){
        int subjCount = output.sessions[i].count;
        for(int x = 0; x < subjCount; x++){
            cout << output.sessions[i].subj[x] << endl;
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
                        cout << "Магическая ошибка" << endl;
                        break;
                    }
                }
            }
        }
    }
    cout << "Студент не найден!" << endl;
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
            cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
            printf_s("%s, %s, %d, %s, %s, %d \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group, output1.zachetka);
            cout << "Введите номер действия: " << endl;
            cout << "1. Изменить ФИО." << endl;
            cout << "2. Изменить дату рождения" << endl;
            cout << "3. Изменить год поступления." << endl;
            cout << "4. Изменить кафедру." << endl;
            cout << "5. Изменить группу." << endl;
            cout << "6. Изменить номер зачётки." << endl;
            cout << "7. Изменить пол." << endl;
            cout << "8. Изменить информацию о сессиях." << endl;
            string action;
            getline(cin, action);
            while(!Utils::isValid(action)){
                while(stoi(action) < 1 && stoi(action) > 8) {
                    cout << "Выбрано неверное действие, повторите ввод." << endl;
                    getline(cin, action);
                }
            }
            string fa, name, ot, fio, date, fak, kaf, group;
            switch (stoi(action)) {
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
                    while (!Utils::isValid(temp2)) {
                        cout << "Номер введён некорректно! Повторите ввод." << endl;
                        getline(cin, temp2);
                    }
                    output1.zachetka = FileUtil::validateStudent(stoi(temp2));
                    cout << "Номер зачётки изменен" << endl;
                    zach = output1.zachetka;
                    break;
                }
                case 7:{
                    cout << "Введите пол. 1 - М, 2 - Ж" << endl;
                    string gender;
                    getline(cin, gender);
                    while (!Utils::isValid(gender)) {
                        cout << "Введите пол. 1 - М, 2 - Ж" << endl;
                        getline(cin, gender);
                    }
                    while (stoi(gender) != 1 && stoi(gender) != 2) {
                        cout << "Введите пол. 1 - М, 2 - Ж" << endl;
                        getline(cin, gender);
                    }
                    output1.gender = stoi(gender);
                    cout << "Пол изменен." << endl;
                    break;
                }
                case 8:{
                    int x;
                    string str;
                    cout << "Введите количество сессий" << endl;
                    getline(cin, str);
                    while (!Utils::isValid(str)) {
                        cout << "Введите число от 1 до 9.";
                        getline(cin, str);
                    }
                    while (stoi(str) <= 0 || stoi(str) > 9) {
                        cout << "Введите число от 1 до 9.";
                        getline(cin, str);
                    }
                    output1.sessionsCout = stoi(str);
                    x = stoi(str);
                    x++;
                    for (int y = 1; y < x; y++) {
                        cout << "Введите данные для сессии #" + to_string(y) << endl;
                        string subj, tem;
                        string count;
                        cout << "Введите количество предметов в данной сессии." << endl;
                        getline(cin, count);
                        while (!Utils::isValid(count)) {
                            cout << "Введите цифру от 1 до 10" << endl;
                            getline(cin, count);
                        }
                        while (stoi(count) < 1 || stoi(count) > 10) {
                            cout << "Введите цифру от 1 до 10" << endl;
                            getline(cin, count);
                        }
                        Session session;
                        session.count = stoi(count);
                        for (int num = 0; num < stoi(count); num++) {
                            cout << "Введите предмет." << endl;
                            getline(cin, subj);
                            char ff[100];
                            strcpy(ff, subj.c_str());
                            strcpy_s(session.subj[num], ff);

                            cout << "Введите оценку по предмету " + subj << endl;
                            getline(cin, tem);
                            while (!Utils::isValid(tem)) {
                                cout << "Оценка введена неверно, повторите." << endl;
                                getline(cin, tem);
                            }
                            while (stoi(tem) < 2 || stoi(tem) > 5) {
                                cout << "Оценка введена неверно, повторите. Введите число от 2 до 5." << endl;
                                getline(cin, tem);
                            }
                            session.marks[num] = stoi(tem);
                            output1.sessions[num] = session;
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
    cout << "Студент успешно удалён!" << endl;
    fclose(temp);
    fclose(file);
    remove("temp.dat");
    Utils::open();
}

//TODO Экстренный выход из любого места. Не факт, что надо
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
        while (!Utils::isValid(temp2)) {
            cout << "Номер введён некорректно! Повторите ввод." << endl;
            getline(cin, temp2);
        }
        stud.zachetka = FileUtil::validateStudent(stoi(temp2));
        cout << "Введите пол. 1 - М, 2 - Ж" << endl;
        string gender;
        getline(cin, gender);
        while (!Utils::isValid(gender)) {
            cout << "Введите пол. 1 - М, 2 - Ж" << endl;
            getline(cin, gender);
        }
        while (stoi(gender) != 1 && stoi(gender) != 2) {
            cout << "Введите пол. 1 - М, 2 - Ж" << endl;
            getline(cin, gender);
        }
        stud.gender = stoi(gender);
        int x;
        string str;
        cout << "Введите количество сессий" << endl;
        getline(cin, str);
        while (!Utils::isValid(str)) {
            cout << "Введите число от 1 до 9.";
            getline(cin, str);
        }
        while (stoi(str) <= 0 || stoi(str) > 9) {
            cout << "Введите число от 1 до 9.";
            getline(cin, str);
        }
        stud.sessionsCout = stoi(str);
        x = stoi(str);
        x++;
        for (int y = 1; y < x; y++) {
            cout << "Введите данные для сессии #" + to_string(y) << endl;
            string subj, tem;
            string count;
            cout << "Введите количество предметов в данной сессии." << endl;
            getline(cin, count);
            while (!Utils::isValid(count)) {
                cout << "Введите цифру от 1 до 10" << endl;
                getline(cin, count);
            }
            while (stoi(count) < 1 || stoi(count) > 10) {
                cout << "Введите цифру от 1 до 10" << endl;
                getline(cin, count);
            }
            Session session;
            session.count = stoi(count);
            for (int num = 0; num < stoi(count); num++) {
                cout << "Введите предмет." << endl;
                getline(cin, subj);
                char ff[100];
                strcpy(ff, subj.c_str());
                strcpy_s(session.subj[num], ff);

                cout << "Введите оценку по предмету " + subj << endl;
                getline(cin, tem);
                while (!Utils::isValid(tem)) {
                    cout << "Оценка введена неверно, повторите." << endl;
                    getline(cin, tem);
                }
                while (stoi(tem) < 2 || stoi(tem) > 5) {
                    cout << "Оценка введена неверно, повторите. Введите число от 2 до 5." << endl;
                    getline(cin, tem);
                }
                session.marks[num] = stoi(tem);
                stud.sessions[num] = session;
            }

        }
        cout << "Данные студента успешно сохранены!" << endl;
        FILE *file;
        file = fopen("person.dat", "a+t");
        fwrite(&stud, sizeof(struct Student), 1, file);
        fclose(file);
    }




