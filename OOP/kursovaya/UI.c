#include "menu.c"

#define AMOUNT_OF_MENUS 1

struct UI {
    struct menu *menus[AMOUNT_OF_MENUS];
};

struct UI* getUI() {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));
    ui->menus[0] = getMainMenu();
    return ui;
}

void runUI(struct UI *ui) {
    int iItem = 0; //Отвечает какой пункт меню активен в данный момент
    int nLast = 2; //Отвечает какой индекс у последнего пункта меню
    char key = 0;
    int isEnable = 1;
    system("cls");
    struct menu* menu = getMainMenu();
    showMenu(menu, 0);
    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); //Вверх
            if(iItem > 0)
                iItem -= 1;
            else
                iItem = nLast;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Вниз
            if(iItem < nLast)
                iItem += 1;
            else
                iItem = 0;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //Enter
            showMenu(menu, iItem);
            
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
                return;
                break;
            }
        }
    }
}