#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#include "student.h"


WCHAR* random_string(WCHAR* set, int length) {
    WCHAR* result = (WCHAR*)malloc((length + 1) * sizeof(WCHAR));
    int set_length = wcslen(set);
    for (int i = 0; i < length; i++) {
        int index = rand() % set_length;
        result[i] = set[index]; 
    }
    result[length] = L'\0';
    return result;
}


WCHAR* random_date() {
    WCHAR* result = (WCHAR*)malloc(11 * sizeof(WCHAR));
    int day = rand() % 31 + 1;
    int month = rand() % 12 + 1;
    int year = rand() % 23 + 2000;
    wsprintfW(result, L"%02d.%02d.%04d\0", day, month, year);
    return result;
}


struct student random_student() {
    struct student result; 
    result.number = rand() % 100 + 1; 
    wcscpy(result.group, random_string(L"it", 2)); 
    wcscat(result.group, random_string(L"12345678", 1)); 
    wcscpy(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); 
    wcscat(result.FIO, random_string(L"abcdefghijklmnopqrstuvwxyz", rand() % 10 + 3)); 
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); 
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1));
    wcscpy(result.birthday, random_date()); 
    result.gender = rand() % 2;
    result.missedHours = rand() % 100;
    result.justifiedHours = rand() % (result.missedHours + 1);
    return result;
}


struct student* generateStudents(int amount) {
    srand(time(NULL));
    struct student* students = (struct student*)malloc(amount*sizeof(struct student));
    for (int i = 0; i < amount; i++) {
        students[i] = random_student();
    }
    return students;
}