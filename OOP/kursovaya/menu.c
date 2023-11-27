#include "menu.h"

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, WCHAR **_points, void (**_functions)()) {
    struct menu *menu = (struct menu*)malloc(sizeof(struct menu));
    menu->choice = 0;
    menu->pointsAmount = _pointsAmount;
    menu->start = _start;
    menu->end = _end;
    menu->points = _points;
    menu->functions = _functions;
    return menu;
}

void showMenu(struct menu *menu, int choice) {   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = menu->start.X;
    int y = menu->start.Y;
    for (int i = 0; i < menu->pointsAmount; i++) {
        gotoxy(x, y++);
        if (i == choice) {
            SetConsoleTextAttribute(hConsole, 5);
            wprintf(L"> ");
            printItem(menu, i);
            SetConsoleTextAttribute(hConsole, 1);
        }
        else {
            wprintf(L"  ");
            printItem(menu, i);
        }
    }
}

void printItem(struct menu *menu, int item) {
    //_tprintf(_T("%s"), menu->points[item]);
    wprintf(menu->points[item]);
}

void runMenu(struct menu *menu) {
    int iItem = 0;
    int isEnable = 1;

    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
            if(iItem > 0)
                iItem -= 1;
            else
                iItem = menu->pointsAmount-1;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(iItem < menu->pointsAmount-1)
                iItem += 1;
            else
                iItem = 0;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            menu->functions[iItem]();
            showMenu(menu, iItem);   
        }
        if(GetAsyncKeyState(VK_ESCAPE)) {
            isEnable = 0;
        }
    }
}