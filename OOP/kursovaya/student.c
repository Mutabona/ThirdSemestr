#include "student.h"

WCHAR* studentToString(struct student student) {
    WCHAR* str = (WCHAR*)malloc(128*sizeof(WCHAR));
    wsprintfW(str, L"%d %s %s %s %d %d %d", student.number, student.group, student.FIO, student.birthday, student.gender, student.missedHours, student.justifiedHours);
    return str;
}

struct student newStudent() {
    struct student student;
    student.number = 0;
    wsprintfW(student.group, L"");
    wsprintfW(student.FIO, L"");
    wsprintfW(student.birthday, L"");
    student.gender = 0;
    student.missedHours = 0;
    student.justifiedHours = 0;
    return student;
}