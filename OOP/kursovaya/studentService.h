#ifndef STUDENT_SERVICE
#define STUDENT_SERVICE

#include "tree.h"

struct studentService {
    int lastId;
    int studentsAmount;
    int lastFoundStudentsAmount;
    struct node* studentRepository; 
};

void addStudent(struct studentService* studentService, struct student student);
void removeStudent(struct studentService* studentService, int id);
struct student* getAllStudents(struct studentService* studentService);
struct studentService* getStudentService();
struct student* getStudentsByFIO(struct studentService* studentService, WCHAR FIO[30]);
struct student* getStudentByNumber(struct studentService* studentService, int number);
struct student* getStudentsByGroup(struct studentService* studentService, WCHAR group[6]);
struct student* getStudentsByBirthday(struct studentService* studentService, WCHAR birthday[11]);
struct student* getStudentsByGender(struct studentService* studentService, int gender);
struct student* getStudentsByJustifiedHours(struct studentService* studentService, int justifiedHours);
struct student* getStudentsByMissedHours(struct studentService* studentService, int missedHours);
struct student* getStudentsWithUnjustifiedHours(struct studentService* studentService);
void loadStudentsFromFile(struct studentService* studentService, char *filename);
void saveStudentsToFile(struct studentService* studentService, char *filename);
void loadStudentsFromBinaryFile(struct studentService* studentService, char *filename);
void saveStudentsToBinaryFile(struct studentService* studentService, char *filename);
void freeStudents(struct studentService* studentService);
WCHAR* getStats(struct studentService* studentService);

void fillStudentRepository(struct studentService* studentService);


#endif