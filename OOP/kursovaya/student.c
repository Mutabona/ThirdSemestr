#include "student.h"

WCHAR* studentToString(struct student student) {
    WCHAR* str = (WCHAR*)malloc(128*sizeof(WCHAR));

    //wprintf(L"Дебаг: %d %s %s %s %d %d %d\n", student.number, student.group, student.FIO, student.birthday, student.gender, student.missedHours, student.justifiedHours);
    wsprintfW(str, L"%d %s %s %s %d %d %d", student.number, student.group, student.FIO, student.birthday, student.gender, student.missedHours, student.justifiedHours);
    return str;
}