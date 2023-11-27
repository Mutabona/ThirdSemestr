#ifndef SCROLLMENU
#define SCROLLMENU

#include "menu.h"
#include "student.h"
#include "studentService.h"

struct scrollMenu {
    struct menu menu;
    struct student* buffer;
    int page;
};

struct scrollMenu* getScrollMenu(struct studentService* studentService, int _pointsAmount, COORD _start, COORD _end);
void updateScrollMenu(struct scrollMenu* smenu);
void showMenu(struct menu *menu, int choice);
void showScrollMenu(struct scrollMenu *menu, int choice);
void printScrollItem(struct scrollMenu *menu, int item);
void runScrollMenu(struct scrollMenu *menu);


#endif