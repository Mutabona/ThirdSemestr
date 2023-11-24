

//#include "student.c"
#include "tree.c"

struct studentService {
    int studentsAmount;
    struct node* studentRepository; 
};

struct student* getAllStudents(struct studentService* studentService) {
    struct student* students = (struct student*)malloc((studentService->studentsAmount)*sizeof(struct student));
    int *i = 0;
    getStudents(studentService->studentRepository, students, i);
    return students;
}