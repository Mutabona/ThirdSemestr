#include "scrollMenu.h"

struct scrollMenu* getScrollMenu(struct student* _buffer, int _pointsAmount, int _bufferPointsAmount, COORD _start, COORD _end) {
    struct scrollMenu *smenu = (struct scrollMenu*)malloc(sizeof(struct scrollMenu));
    smenu->page = 0;
    smenu->buffer = _buffer;
    smenu->bufferPointsAmount = _bufferPointsAmount;
    smenu->menu.choice = 0;
    smenu->menu.pointsAmount = _pointsAmount;
    smenu->menu.start = _start;
    smenu->menu.end = _end;

    smenu->menu.points = (WCHAR**)malloc(smenu->menu.pointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < smenu->menu.pointsAmount; i++) {
        smenu->menu.points[i] = (WCHAR*)malloc(128*sizeof(WCHAR));
    }

    updateScrollMenu(smenu);

    return smenu;
}

void updateScrollMenu(struct scrollMenu* smenu) {
    if (!(smenu->buffer)) return;
    int start = smenu->page * smenu->menu.pointsAmount;
    for(int i = 0; i < smenu->menu.pointsAmount && (start + i) < smenu->bufferPointsAmount; i++) {
        smenu->menu.points[i] = studentToString(smenu->buffer[start+i]);
    }
    //smenu->menu.functions = _functions;
}

void showScrollMenu(struct scrollMenu *smenu, int choice) {
    if (!(smenu->buffer)) return;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = smenu->menu.start.X;
    int y = smenu->menu.start.Y;
    int start = smenu->page * smenu->menu.pointsAmount;
    for (int i = 0; i < smenu->menu.pointsAmount && (start + i) < smenu->bufferPointsAmount; i++) {
        gotoxy(x, y++);
        if (i == choice) {
            SetConsoleTextAttribute(hConsole, 5);
            wprintf(L"> ");
            printScrollItem(smenu, i);
            SetConsoleTextAttribute(hConsole, 1);
        }
        else {
            wprintf(L"  ");
            printScrollItem(smenu, i);
        }
    }
}

void printScrollItem(struct scrollMenu *smenu, int item) {
    //_tprintf(_T("%s"), menu->points[item]);
    wprintf(smenu->menu.points[item]);
}

void runScrollMenu(struct scrollMenu *smenu) {
    if (!(smenu->buffer)) return;
    int iItem = 0; 
    int isEnable = 1;

    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
            if(iItem > 0)
                iItem -= 1;
            else {
                if (smenu->page > 0) {
                    smenu->page--;
                    iItem = 0;
                    updateScrollMenu(smenu);
                }
            }
            showScrollMenu(smenu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(iItem < smenu->menu.pointsAmount-1)
                iItem += 1;
            else {
                if (smenu->page < smenu->bufferPointsAmount/smenu->menu.pointsAmount) {
                    smenu->page++;
                    iItem = 0;
                    updateScrollMenu(smenu);
                }
            }
            showScrollMenu(smenu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            smenu->menu.functions[iItem]();
            showScrollMenu(smenu, iItem);   
        }
        if(GetAsyncKeyState(VK_ESCAPE)) {
            isEnable = 0;
        }
    }
}