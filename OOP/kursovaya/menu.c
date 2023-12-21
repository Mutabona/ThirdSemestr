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
    printMenuBorders(menu->start, menu->end);  
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
    for (int y = menu->start.Y-1; y < menu->end.Y+1; y++) {
        gotoxy(menu->start.X-1, y);
        for (int x = menu->start.X-1; x < menu->end.X+2; x++) {
            wprintf(L" ");
        }
    }
}

void printMenuBorders(COORD start, COORD end) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 1);
    
    gotoxy(start.X-1, start.Y-1);
    wprintf(L"+");
    for(int i = start.X-1; i < end.X; i++) {
        wprintf(L"-");
    }
    wprintf(L"+");

    for(int i = start.Y; i < end.Y; i++) {
        gotoxy(start.X - 1, i);
        wprintf(L"|");
        gotoxy(end.X + 1, i);
        wprintf(L"|");
    }

    gotoxy(start.X-1, end.Y);
    wprintf(L"+");
    for(int i = start.X-1; i < end.X; i++) {
        wprintf(L"-");
    }
    wprintf(L"+");
}