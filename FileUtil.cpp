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
} typedef Session;

struct Student{
    char name[40];
    char birth[15];
    int postup;
    char kaf[25];
    char group[10];
    int zachetka;
    Session sessions[9];
    int gender;
} typedef Student;

int FileUtil::validateStudent(int num){
    FILE *file;
    file = fopen("person.dat", "r+");
    struct Student output;
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
                fclose(file);
                if(stoi(temp) == 0){
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
    struct Student output;
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
    int n = FileUtil::getStudentCount();
    file = fopen("person.dat", "r+");
    cout << "ФИО | Дата рождения | Год поступления | Кафедра | Группа | Номер зачётки" << endl;
    for (int i = 0; i < n; i++) {
        Student output1;
        fread(&output1, sizeof(struct Student), 1, file);
        printf_s("%s, %s, %d, %s, %s, %d \n", output1.name, output1.birth, output1.postup, output1.kaf, output1.group,
                 output1.zachetka);
        fclose(file);
    }
}


//TODO Экстренный выход из любого места. Не факт, что надо
    void FileUtil::enterStudent() {
        Student stud;
        string fa, name, ot, fio, date, kaf, group;
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
        cout << "Введите факультет, кафедру." << endl;
        getline(cin, kaf);
        strcpy_s(stud.kaf, kaf.c_str());
        cout << "Введите группу." << endl;
        getline(cin, group);
        strcpy_s(stud.group, group.c_str());
        cout << "Введите номер зачётки." << endl;
        string temp2;
        getline(cin, temp2);
        if (!Utils::isValid(temp2)) {
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
            for (int num = 0; num < stoi(count); num++) {
                Session session;
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
        file = fopen("person.dat", "a");
        fwrite(&stud, sizeof(struct Student), 1, file);
        fclose(file);
    }


    Student FileUtil::findStudent(int zach) {
        FILE *file;
        file = fopen("person.dat", "r+");
        Student output;
        while (!feof(file)) {
            if (fread(&output, sizeof(struct Student), 1, file)) {
                if (output.zachetka == zach) {
                    fclose(file);
                    return output;
                }
            }
        }
        fclose(file);
        return output;
    }

    void FileUtil::test() {
        FILE *file2;
        int n = FileUtil::getStudentCount();
        file2 = fopen("person.dat", "r+");
        for (int i = 0; i < n; i++) {
            Student output1;
            fread(&output1, sizeof(struct Student), 1, file2);
            if (output1.zachetka == 123321) {
                cout << "Хуила пойман" << endl;
                string name;
                getline(cin, name);
                strcpy_s(output1.kaf, name.c_str());
            }
        }
        fclose(file2);
        /*   FILE *file;
           file = fopen ("person.dat", "a+t");
           if (file == NULL) {
               fprintf(stderr, "Что-то не так, перезапустите!\n");
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



