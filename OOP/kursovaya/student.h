#ifndef STUDENT
#define STUDENT

#include <windows.h>

struct student {
    int number;
    char group[6];
    char FIO[30];
    char birthday[11];
    int gender;
    int missedHours;
    int justifiedHours;
};

WCHAR* studentToString(struct student student);

#endif