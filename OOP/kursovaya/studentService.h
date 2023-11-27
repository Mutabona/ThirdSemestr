#ifndef STUDENT_SERVICE
#define STUDENT_SERVICE

#include "tree.h"

struct studentService {
    int studentsAmount;
    struct node* studentRepository; 
};

void addStudent(struct studentService* studentService, struct student student);
struct student* getAllStudents(struct studentService* studentService);
struct studentService* getStudentService();

void fillStudentRepository(struct studentService* studentService);

#endif