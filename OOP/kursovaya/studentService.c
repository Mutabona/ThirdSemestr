#include "studentService.h"

#include "generateRandomStudents.c"

void addStudent(struct studentService* studentService, struct student student) {    
    student.number = studentService->studentsAmount++;
    studentService->studentRepository = addNode(studentService->studentRepository, student);
    return;
}

struct student* getAllStudents(struct studentService* studentService) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc((studentService->studentsAmount)*sizeof(struct student));
    getStudents(studentService->studentRepository, students, 0);
    return students;
}

struct studentService* getStudentService() {
    struct studentService* studentService = (struct studentService*)malloc(sizeof(struct studentService));
    studentService->studentsAmount = 0;
    studentService->lastFoundStudentsAmount = 0;
    studentService->studentRepository = NULL;
    return studentService;
}

void fillStudentRepository(struct studentService* studentService) {
    int amount = 5;
    struct student* students = generateStudents(amount);
    for (int i = 0; i < amount; i++) {
        addStudent(studentService, students[i]);
    }
}

struct student* getStudentsByFIO(struct studentService* studentService, WCHAR FIO[30]) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(sizeof(struct student));
    studentService->lastFoundStudentsAmount = getStudentsListByFIO(studentService->studentRepository, students, 0, FIO);
    return students;
}

struct student* getStudentByNumber(struct studentService* studentService) {

}

struct student* getStudentsByGroup(struct studentService* studentService) {

}

struct student* getStudentsByBirthday(struct studentService* studentService) {

}

struct student* getStudentsByGender(struct studentService* studentService) {

}

struct student* getStudentsByJustifiedHours(struct studentService* studentService) {

}

struct student* getStudentsByMissedHours(struct studentService* studentService) {

}