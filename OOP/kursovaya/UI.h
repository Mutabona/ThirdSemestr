#ifndef USERINTERFACE
#define USERINTERFACE

#include <stdio.h>
#include <locale.h>

#include "menu.h"
#include "studentService.h"
#include "scrollMenu.h"

#define AMOUNT_OF_MENUS 1
#define AMOUNT_OF_SMENUS 1

struct UI {
    struct menu *menus[AMOUNT_OF_MENUS];
    struct scrollMenu *scrollMenus[AMOUNT_OF_SMENUS];
};

struct UI* getUI(struct studentService *studentService);
void runUI(struct UI *ui);
void printBorders();

#endif