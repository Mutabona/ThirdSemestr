#ifndef STUDENT
#define STUDENT

#include <windows.h>
#include <stdio.h>

struct student {
    int number;
    WCHAR group[6];
    WCHAR FIO[30];
    WCHAR birthday[11];
    int gender;
    int missedHours;
    int justifiedHours;
};

WCHAR* studentToString(struct student student);
WCHAR* studentWithUnjustifiedHoursToString(struct student student);
struct student* newStudent();

#endif