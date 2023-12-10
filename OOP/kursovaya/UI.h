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
    struct menu *fileMenu;
    struct scrollMenu *badStudentsMenu;
};

struct UI* getUI(struct studentService *studentService);
void runUI(struct UI *ui);
int initMainMenu(struct UI* ui);
int initScrollMenu(struct UI* ui);
void updateScrollBuffer(struct UI* ui);
void updateBadBuffer(struct UI* ui);
int initStudentMenu(struct student* student);
struct student* findStudent(struct UI* ui);
void hidecursor();
char* getFileName(struct UI* ui);
int initFileMenu(struct UI* ui);
int initBadStudentsMenu(struct UI* ui);
void freeUI(struct UI *ui);

#endif