#include "studentService.h"

#include "generateRandomStudents.c"

void addStudent(struct studentService* studentService, struct student student) {    
    student.number = studentService->lastId++;
    studentService->studentsAmount++;
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
    studentService->lastId = 0;
    studentService->studentRepository = NULL;
    return studentService;
}

void fillStudentRepository(struct studentService* studentService) {
    int amount = 180;
    struct student* students = generateStudents(amount);
    for (int i = 0; i < amount; i++) {
        addStudent(studentService, students[i]);
    }
    printf("Test students loaded\n");
}

struct student* getStudentsByFIO(struct studentService* studentService, WCHAR FIO[30]) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByFIO(studentService->studentRepository, students, 0, FIO);
    studentService->lastFoundStudentsAmount = foundStudents;   
    if (!foundStudents) return NULL; 
    return students;
}

struct student* getStudentByNumber(struct studentService* studentService, int number) {
    struct student* student = _getStudentByNumber(studentService->studentRepository, number);
    studentService->lastFoundStudentsAmount = student?1:0;
    return student;
}

struct student* getStudentsByGroup(struct studentService* studentService, WCHAR group[6]) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByGroup(studentService->studentRepository, students, 0, group);
    studentService->lastFoundStudentsAmount = foundStudents;
    if (!foundStudents) return NULL;
    return students;
}

struct student* getStudentsByBirthday(struct studentService* studentService, WCHAR birthday[11]) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByBirthday(studentService->studentRepository, students, 0, birthday);
    studentService->lastFoundStudentsAmount = foundStudents;
    if (!foundStudents) return NULL;
    return students;
}

struct student* getStudentsByGender(struct studentService* studentService, int gender) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByGender(studentService->studentRepository, students, 0, gender);
    studentService->lastFoundStudentsAmount = foundStudents;
    if (!foundStudents) return NULL;
    return students;
}

struct student* getStudentsByJustifiedHours(struct studentService* studentService, int justifiedHours) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByJustifiedHours(studentService->studentRepository, students, 0, justifiedHours);
    studentService->lastFoundStudentsAmount = foundStudents;
    if (!foundStudents) return NULL;
    return students;
}

struct student* getStudentsByMissedHours(struct studentService* studentService, int missedHours) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListByMissedHours(studentService->studentRepository, students, 0, missedHours);
    studentService->lastFoundStudentsAmount = foundStudents;
    if (!foundStudents) return NULL;
    return students;
}

struct student* getStudentsWithUnjustifiedHours(struct studentService* studentService) {
    if (!studentService->studentRepository) return NULL;
    struct student* students = (struct student*)malloc(studentService->studentsAmount * sizeof(struct student));
    int foundStudents = getStudentsListWithUnjustifiedHours(studentService->studentRepository, students, 0);
    studentService->lastFoundStudentsAmount = foundStudents;
    
    if (!foundStudents) {
        studentService->lastFoundStudentsAmount = 0;
        return NULL;
    }
    return students;
}

void removeStudent(struct studentService* studentService, int id) {
    studentService->studentRepository = removeNode(studentService->studentRepository, id);
    studentService->studentsAmount--;
}

void loadStudentsFromFile(struct studentService* studentService, char *filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return;
    }
    int *i = (int*)malloc(sizeof(int));
    studentService->studentRepository = NULL;
    studentService->studentRepository = loadFromFile(studentService->studentRepository, file, i);
    studentService->studentsAmount=*i;
    studentService->lastId=*i;
    fclose(file);
}

void saveStudentsToFile(struct studentService* studentService, char *filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        return;
    }
    saveToFile(studentService->studentRepository, file);
    fclose(file);
}

void loadStudentsFromBinaryFile(struct studentService* studentService, char *filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return;
    }
    int *i = (int*)malloc(sizeof(int));
    studentService->studentRepository = NULL;
    studentService->studentRepository = loadFromFile(studentService->studentRepository, file, i);
    studentService->studentsAmount=*i;
    studentService->lastId=*i;
    fclose(file);
}

void saveStudentsToBinaryFile(struct studentService* studentService, char *filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return;
    }
    saveToFile(studentService->studentRepository, file);
    fclose(file);
}

void freeStudents(struct studentService* studentService) {
    freeTree(studentService->studentRepository);
    free(studentService);
}

WCHAR* getStats(struct studentService* studentService) {
    int missedHours = getMissedHours(studentService->studentRepository);
    int justifiedHours = getJustifiedHours(studentService->studentRepository);
    float unjustifiedHoursPercent = 0.0;
    int unjustifiedHours = missedHours - justifiedHours;
    if (justifiedHours == 0 && missedHours == 0) {
        unjustifiedHoursPercent = 0;
    }
    else if (justifiedHours == 0) {
        unjustifiedHoursPercent = 100;
    }
    else {
        unjustifiedHoursPercent = (unjustifiedHours * 1.0 / missedHours)*100;
    }
    WCHAR* str = (WCHAR*)malloc(120*sizeof(WCHAR));
    wsprintfW(str, L"Пропущено часов: %d, оправдано часов: %d, неоправдано часов: %d, процент неоправданных пропусков %d", missedHours, justifiedHours, unjustifiedHours, (int)unjustifiedHoursPercent);
    return str;
}