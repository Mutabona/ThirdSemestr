#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include "menu.c"


int main() {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int iItem = 0; //Отвечает какой пункт меню активен в данный момент
    int nLast = 2; //Отвечает какой индекс у последнего пункта меню
    char key = 0;
    int isEnable = 1;
    struct menu* menu = getMenu();
    showMenu(menu, 0);
    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); //Вверх
            if(iItem > 0)
                iItem -= 1;
            else
                iItem = nLast;
            //ShowMenu(iItem);
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Вниз
            if(iItem < nLast)
                iItem += 1;
            else
                iItem = 0;
            //ShowMenu(iItem);
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Enter
            showMenu(menu, iItem);
            //ShowMenu(iItem);
            
            switch(iItem)
            {
            case 0:
                printf("Run 1-st item of menu\n");
                break;
            case 1:
                printf("Run 2-nd item of menu\n");
                break;
            case 2:
                printf("Leave\n");
                return 0;
                break;
            }
        }
    }
}