#ifndef STUDENT_SERVICE
#define STUDENT_SERVICE

#include "tree.h"

struct studentService {
    int studentsAmount;
    int lastFoundStudentsAmount;
    struct node* studentRepository; 
};

void addStudent(struct studentService* studentService, struct student student);
struct student* getAllStudents(struct studentService* studentService);
struct studentService* getStudentService();
struct student* getStudentsByFIO(struct studentService* studentService, WCHAR FIO[30]);

void fillStudentRepository(struct studentService* studentService);


#endif