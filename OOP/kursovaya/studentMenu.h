#ifndef STUDENTMENU
#define STUDENTMENU

#include "menu.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

struct studentMenu {
    struct menu menu;
    struct student* student;
};

struct studentMenu* getStudentMenu(struct student *student);
void updateStudentMenu(struct studentMenu* menu);
void changeStudentMenu(struct studentMenu* menu, int item);

#endif