#include "studentService.h"

struct student* getAllStudents(struct studentService* studentService) {
    struct student* students = (struct student*)malloc((studentService->studentsAmount)*sizeof(struct student));
    int *i = 0;
    getStudents(studentService->studentRepository, students, i);
    return students;
}

struct studentService* getStudentService() {
    struct studentService* studentService = (struct studentService*)malloc(sizeof(struct studentService));
    studentService->studentsAmount = 0;
    studentService->studentRepository = NULL;
    return studentService;
}