#ifndef SCROLLMENU
#define SCROLLMENU

#include "menu.h"
#include "student.h"
#include "studentService.h"

struct scrollMenu {
    struct menu menu;
    struct student* buffer;
    int bufferPointsAmount;
    int maxPoints;
    int page;
};

struct scrollMenu* getScrollMenu(struct student* buffer, int _pointsAmount, int bufferPointsAmount, COORD _start, COORD _end);
void updateScrollMenu(struct scrollMenu* smenu);
//void showScrollMenu(struct scrollMenu *menu, int choice);
int runScrollMenu(struct scrollMenu *menu);
//void clearScrollMenu(struct scrollMenu* scrollMenu);
int getAmountOfElementsOnPage(struct scrollMenu *smenu);

#endif