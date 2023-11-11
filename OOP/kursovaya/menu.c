#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>

#define AMOUNT_OF_POINTS 3

struct menu* getMenu();
void showMenu(struct menu *menu, int choice);
void printItem(struct menu *menu, int item);

struct menu {
    int choice;
    int pointsAmount;
    TCHAR *points[15];
};

struct menu* getMenu() {
    struct menu *menu = (struct menu*)malloc(sizeof(struct menu));
    menu->choice = 0;
    menu->pointsAmount = AMOUNT_OF_POINTS;
    menu->points[0] = L"Один";
    menu->points[1] = L"Два";
    menu->points[2] = L"Выход";

    return menu;
}

void showMenu(struct menu *menu, int choice) {   
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < menu->pointsAmount; i++) {
        if (i == choice) {
            SetConsoleTextAttribute(hConsole, 5);
            wprintf(L"> ");
            printItem(menu, i);
            SetConsoleTextAttribute(hConsole, 1);
        }
        else {
            printItem(menu, i);
        }
    }
}

void printItem(struct menu *menu, int item) {
    wprintf(L"%s\n", menu->points[item]);
}