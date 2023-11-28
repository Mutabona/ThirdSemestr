#ifndef STUDENTMENU
#define STUDENTMENU

#include "menu.h"
#include "student.h"

struct studentMenu {
    struct menu menu;
};

struct studentMenu* getStudentMenu(struct student *student);
int runStudentMenu(struct student *student);

#endif