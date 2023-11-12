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

struct menu* getMainMenu();
void showMenu(struct menu *menu, int choice);
void printItem(struct menu *menu, int item);

struct menu {
    int choice;
    int pointsAmount;
    COORD start, end;
    TCHAR *points[15];
};

struct menu* getMainMenu() {
    struct menu *menu = (struct menu*)malloc(sizeof(struct menu));
    menu->choice = 0;
    menu->pointsAmount = 3;
    COORD start, end;
    start.X = 1; start.Y = 1;
    end.X = 1; end.Y = 16;
    menu->start = start;
    menu->end = end;
    menu->points[0] = L"Один";
    menu->points[1] = L"Два";
    menu->points[2] = L"Выход";

    return menu;
}

void showMenu(struct menu *menu, int choice) {   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = menu->start.X;
    int y = menu->start.Y;
    for (int i = 0; i < menu->pointsAmount; i++) {
        gotoxy(x, y++);
        if (i == choice) {
            set_display_atrib(1);
            SetConsoleTextAttribute(hConsole, 5);
            wprintf(L"> ");
            printItem(menu, i);
            SetConsoleTextAttribute(hConsole, 1);
            resetcolor();
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