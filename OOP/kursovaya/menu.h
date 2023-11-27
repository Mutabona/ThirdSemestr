#ifndef MENU
#define MENU

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

struct menu {
    int choice;
    int pointsAmount;
    COORD start, end;
    WCHAR **points;
    void (**functions)(void);
};

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, WCHAR **_points, void (**_functions)());
void showMenu(struct menu *menu, int choice);
void printItem(struct menu *menu, int item);
void runMenu(struct menu *menu);

#endif