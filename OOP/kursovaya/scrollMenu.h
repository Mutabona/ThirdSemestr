#ifndef SCROLLMENU
#define SCROLLMENU

#include "menu.h"
#include "student.h"
#include "studentService.h"

struct scrollMenu {
    struct menu* menu;
    struct student* buffer;
    int bufferPointsAmount;
    int maxPoints;
    int page;
    int printStudentsMode;
};

struct scrollMenu* getScrollMenu(struct student* buffer, int _pointsAmount, int bufferPointsAmount, COORD _start, COORD _end, int _printStudentsMode);
void updateScrollMenu(struct scrollMenu* smenu);
int runScrollMenu(struct scrollMenu *menu);
int getAmountOfElementsOnPage(struct scrollMenu *smenu);
void printHeader(struct scrollMenu* smenu);
void clearHeader(struct scrollMenu* smenu);

#endif