//
// Created by Delta on 18.05.2020.
//

#ifndef KURSACHNEW_FILEUTIL_H
#define KURSACHNEW_FILEUTIL_H


class FileUtil {

public:
    static int getStudentCount();
    static bool checkFile();
    static void printAll();
    static bool isEmpty();
    static void enterStudent();
    static bool validateStudent(const char[]);
    static void studentAction(const char[], int);
    static void recreateFileWithDelete(const char[]);
    static void recreateFileWithEdit(const char[]);
    static void allStudentMarks(const char[]);
    static void printMarks(struct Student);
    static void sorting(int);
    static bool calculate(int, struct Student);
    static bool genderCheck(int, struct Student);
};


#endif //KURSACHNEW_FILEUTIL_H
