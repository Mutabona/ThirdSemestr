#include "menu.h"
#include "studentService.h"

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, WCHAR **_points) {
    struct menu *menu = (struct menu*)malloc(sizeof(struct menu));
    menu->choice = 0;
    menu->pointsAmount = _pointsAmount;
    menu->start = _start;
    menu->end = _end;
    menu->points = _points;
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
    wprintf(menu->points[item]);
}

int runMenu(struct menu *menu) {
    int iItem = 0;
    int isEnable = 1;

    showMenu(menu, iItem);

    //gotoxy(6,2);

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
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            return iItem;   
        }
        if(GetAsyncKeyState(VK_ESCAPE)) {
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
            return -1;
        }
    }
}

int runSubMenu(struct menu *menu) {
    int iItem = 0;
    int isEnable = 1;

    showMenu(menu, iItem);

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
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            clearMenu(menu);
            return iItem;   
        }
        if(GetAsyncKeyState(VK_LEFT)) {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
            clearMenu(menu);
            return -1;
        }
    }
}

void clearMenu(struct menu* menu) {
    for (int y = menu->start.Y; y < menu->end.Y; y++) {
        gotoxy(menu->start.X, y);
        for (int x = menu->start.X; x < menu->end.X; x++) {
            wprintf(L" ");
        }
    }
}