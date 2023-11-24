#include <stdio.h>
#include <locale.h>

//#include "menu.c"
//#include "studentService.c"
#include "scrollMenu.c"

#define AMOUNT_OF_MENUS 1
#define AMOUNT_OF_SMENUS 1

struct UI {
    struct menu *menus[AMOUNT_OF_MENUS];
    struct scrollMenu *scrollMenus[AMOUNT_OF_SMENUS];
};

struct UI* getUI(struct studentService *studentService) {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    int mainMenuPointsAmount = 4;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = 2; mainMenuEnd.Y = 17;

    WCHAR **mainMenuPoints;
    mainMenuPoints = (WCHAR**)malloc(mainMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        mainMenuPoints[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }
    mainMenuPoints[0] = L"Добавить";
    mainMenuPoints[1] = L"Убрать";
    mainMenuPoints[2] = L"Вывести";
    mainMenuPoints[3] = L"Kukaracha";
    

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

    int scrollMenuPointsAmount = 15;

    COORD scrollMenuStart, scrollMenuEnd;
    scrollMenuStart.X = 15; scrollMenuStart.Y = 2;
    scrollMenuEnd.X = 15; scrollMenuEnd.Y = 17;

    ui->scrollMenus[0] = getScrollMenu(studentService,
                                       scrollMenuPointsAmount,
                                       scrollMenuStart,
                                       scrollMenuEnd
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