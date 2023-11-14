#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>

#define ESC "\033"
#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?251");
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) 	printf(ESC "[%dm",color)

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, TCHAR **_points, void (**_functions)());
void showMenu(struct menu *menu, int choice);
void printItem(struct menu *menu, int item);
void runMenu(struct menu *menu);

struct menu {
    int choice;
    int pointsAmount;
    COORD start, end;
    TCHAR **points;
    void (**functions)(void);
};

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, TCHAR **_points, void (**_functions)()) {
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
    wprintf(L"%s", menu->points[item]);
}

void runMenu(struct menu *menu) {
    int iItem = 0; //Отвечает какой пункт меню активен в данный момент
    int isEnable = 1;

    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); //Вверх
            if(iItem > 0)
                iItem -= 1;
            else
                iItem = menu->pointsAmount-1;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Вниз
            if(iItem < menu->pointsAmount-1)
                iItem += 1;
            else
                iItem = 0;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Enter
            menu->functions[iItem]();
            showMenu(menu, iItem);   
        }
        if(GetAsyncKeyState(VK_ESCAPE)) {
            isEnable = 0;
        }
    }
}