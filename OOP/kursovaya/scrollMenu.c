#include "menu.c"
#include "studentService.c"

struct scrollMenu {
    struct menu menu;
    struct student* buffer;
    int page;
};

struct scrollMenu* getScrollMenu(struct studentService* studentService, int _pointsAmount, COORD _start, COORD _end) {
    struct scrollMenu *smenu = (struct scrollMenu*)malloc(sizeof(struct scrollMenu));
    smenu->page = 0;
    smenu->buffer = getAllStudents(studentService);
    smenu->menu.choice = 0;
    smenu->menu.pointsAmount = _pointsAmount;
    smenu->menu.start = _start;
    smenu->menu.end = _end;
    updateScrollMenu(smenu);

    return smenu;
}

void updateScrollMenu(struct scrollMenu* smenu) {
    int start = smenu->page*smenu->menu.pointsAmount;
    for(int i = start; i < start + smenu->menu.pointsAmount; i++) {
        smenu->menu.points[i] = studentToString(smenu->buffer[i]);
    }
    //smenu->menu.functions = _functions;
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

void runScrollMenu(struct scrollMenu *menu) {
    int iItem = 0; //ќтвечает какой пункт меню активен в данный момент
    int isEnable = 1;

    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); //¬верх
            if(iItem > 0)
                iItem -= 1;
            else
                iItem = menu->pointsAmount-1;
            showMenu(menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); //¬низ
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