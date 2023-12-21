#include "student.h"

WCHAR* studentToString(struct student student) {
    WCHAR* str = (WCHAR*)malloc(256*sizeof(WCHAR));
    wsprintfW(str, L"%6d|%7s|%31s|%11s|%4d|%10d|%10d", student.number, student.group, student.FIO, student.birthday, student.gender, student.missedHours, student.justifiedHours);
    return str;
}

WCHAR* studentWithUnjustifiedHoursToString(struct student student) {
    WCHAR* str = (WCHAR*)malloc(256*sizeof(WCHAR));
    wsprintfW(str, L"%6d|%7s|%31s|%20d", student.number, student.group, student.FIO, student.missedHours - student.justifiedHours);
    return str;
}

struct student *newStudent() {
    struct student* student = (struct student*)malloc(sizeof(struct student));
    student->number = 0;
    wsprintfW(student->group, L"");
    wsprintfW(student->FIO, L"");
    wsprintfW(student->birthday, L"");
    student->gender = 0;
    student->missedHours = 0;
    student->justifiedHours = 0;
    return student;
}