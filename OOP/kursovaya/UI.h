#ifndef USERINTERFACE
#define USERINTERFACE

#include <stdio.h>
#include <locale.h>

#include "menu.h"
#include "studentService.h"
#include "scrollMenu.h"
#include "studentMenu.h"

struct UI {
    struct studentService* studentService;
    struct menu *mainMenu;
    struct scrollMenu *scrollMenu;
};

struct UI* getUI(struct studentService *studentService);
void runUI(struct UI *ui);
void printBorders();
int initMainMenu(struct UI* ui);
int initScrollMenu(struct UI* ui);
void updateScrollBuffer(struct UI* ui);
int initStudentMenu(struct student* student);
void findStudent(struct UI* ui);
void hidecursor();

#endif