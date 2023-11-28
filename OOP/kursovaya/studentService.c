#include "studentService.h"

#include "generateRandomStudents.c"

void addStudent(struct studentService* studentService, struct student student) {    
    student.number = studentService->studentsAmount++;
    studentService->studentRepository = addNode(studentService->studentRepository, student);
    return;
}

struct student* getAllStudents(struct studentService* studentService) {
    if (!studentService->studentRepository) return NULL;
    //wprintf(L"Количество студентов: %d", studentService->studentsAmount);
    struct student* students = (struct student*)malloc((studentService->studentsAmount)*sizeof(struct student));
    getStudents(studentService->studentRepository, students, 0);
    // for (int i = 0; i < 20; i++) {
    //     wprintf(L"%d", students[i].number);
    // }
    return students;
}

struct studentService* getStudentService() {
    struct studentService* studentService = (struct studentService*)malloc(sizeof(struct studentService));
    studentService->studentsAmount = 0;
    studentService->studentRepository = NULL;
    return studentService;
}

void fillStudentRepository(struct studentService* studentService) {
    int amount = 35;
    struct student* students = generateStudents(amount);
    for (int i = 0; i < amount; i++) {
        addStudent(studentService, students[i]);
    }
}