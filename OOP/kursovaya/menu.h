#ifndef MENU
#define MENU

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>

#define ESC "\033"
#define home() 			wprintf(ESC L"[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		wprintf(ESC L"[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor() wprintf(ESC L"[?251");
#define resetcolor() wprintf(ESC L"[0m")
#define set_display_atrib(color) 	wprintf(ESC L"[%dm",color)

struct menu {
    int choice;
    int pointsAmount;
    COORD start, end;
    WCHAR **points;
};

struct menu* getMenu(int _pointsAmount, COORD _start, COORD _end, WCHAR **_points);
void showMenu(struct menu *menu, int choice);
void printItem(struct menu *menu, int item);
int runMenu(struct menu *menu);
void clearMenu(struct menu* menu);
int runSubMenu(struct menu *menu);
void printMenuBorders(COORD start, COORD end);

#endif