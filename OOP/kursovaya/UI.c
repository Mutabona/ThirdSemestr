#include <stdio.h>
#include <tchar.h>
#include <locale.h>

#include "menu.c"
#include "tree.c"

#define AMOUNT_OF_MENUS 1

struct UI {
    struct menu *menus[AMOUNT_OF_MENUS];
};

struct UI* getUI() {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    int mainMenuPointsAmount = 4;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = 2; mainMenuEnd.Y = 17;

    TCHAR **mainMenuPoints;
    mainMenuPoints = (TCHAR**)malloc(mainMenuPointsAmount*sizeof(TCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        mainMenuPoints[i] = (TCHAR*)malloc(15*sizeof(TCHAR));
    }
    mainMenuPoints[0] = _T("Добавить");
    mainMenuPoints[1] = _T("Убрать");
    mainMenuPoints[2] = _T("Вывести");
    mainMenuPoints[3] = _T("Kukaracha");
    

    void (**mainMenuFunctions)();
    mainMenuFunctions = malloc(mainMenuPointsAmount*sizeof(void*));
    mainMenuFunctions[0] = addStudent;
    mainMenuFunctions[1] = addStudent;
    mainMenuFunctions[2] = addStudent;
    mainMenuFunctions[3] = addStudent;

    ui->menus[0] = getMenu(
        mainMenuPointsAmount,
        mainMenuStart,
        mainMenuEnd,
        mainMenuPoints,
        mainMenuFunctions
    );

    return ui;
}

void runUI(struct UI *ui) {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    system("cls");

    //printBorders();
    for (int i = 0; i < sizeof(ui->menus)/sizeof(struct menu*); i++) {
        showMenu(ui->menus[i], 0);
    } 

    runMenu(ui->menus[0]);
}

void printBorders() {
    home();
	wprintf(L"");
}