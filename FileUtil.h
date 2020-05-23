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
    static int validateStudent(int);
    static void studentAction(int, int);
    static void recreateFileWithDelete(int);
    static void recreateFileWithEdit(int);
    static void allStudentMarks(int);
    static void printMarks(struct Student);
};


#endif //KURSACHNEW_FILEUTIL_H
