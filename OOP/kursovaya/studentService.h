#ifndef STUDENT_SERVICE
#define STUDENT_SERVICE

#include "tree.h"

struct studentService {
    int studentsAmount;
    struct node* studentRepository; 
};

struct student* getAllStudents(struct studentService* studentService);
struct studentService* getStudentService();

#endif