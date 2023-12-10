#include "scrollMenu.h"
#include "studentMenu.h"

struct scrollMenu* getScrollMenu(struct student* _buffer, int _pointsAmount, int _bufferPointsAmount, COORD _start, COORD _end, int _printStudentsMode) {
    struct scrollMenu *smenu = (struct scrollMenu*)malloc(sizeof(struct scrollMenu));
    smenu->page = 0;
    smenu->buffer = _buffer;
    smenu->bufferPointsAmount = _bufferPointsAmount;
    smenu->menu.choice = 0;
    smenu->menu.pointsAmount = _pointsAmount;
    smenu->menu.start = _start;
    smenu->menu.end = _end;
    smenu->maxPoints = 15;
    smenu->printStudentsMode = _printStudentsMode;

    smenu->menu.points = (WCHAR**)malloc(smenu->menu.pointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < smenu->menu.pointsAmount; i++) {
        smenu->menu.points[i] = (WCHAR*)malloc(128*sizeof(WCHAR));
    }

    return smenu;
}

void updateScrollMenu(struct scrollMenu* smenu) {
    clearMenu(&smenu->menu);
    if (!smenu->buffer) {
        smenu->menu.points[0] = L"Нет таких студентов";
        smenu->menu.pointsAmount = 1;
        return;
    }
    int start = smenu->page * smenu->maxPoints;
    int amountOfElementsOnPage = getAmountOfElementsOnPage(smenu);
    smenu->menu.pointsAmount = amountOfElementsOnPage;
    if (smenu->printStudentsMode == 0) {
        for(int i = 0; i < smenu->menu.pointsAmount; i++) {
            smenu->menu.points[i] = studentToString(smenu->buffer[start+i]);
        }
    }
    else {
        for(int i = 0; i < smenu->menu.pointsAmount; i++) {
            smenu->menu.points[i] = studentWithUnjustifiedHoursToString(smenu->buffer[start+i]);
        }
    }
}

int getAmountOfElementsOnPage(struct scrollMenu *smenu) {
    int amountOfElementsOnPage;
    if ((smenu->bufferPointsAmount - smenu->page * smenu->maxPoints)/smenu->maxPoints > 0) {
        amountOfElementsOnPage = smenu->maxPoints;
    }
    else {
        amountOfElementsOnPage = smenu->bufferPointsAmount - smenu->page * smenu->maxPoints;
    }
    return amountOfElementsOnPage;
}

int runScrollMenu(struct scrollMenu *smenu) {
    updateScrollMenu(smenu);
    int iItem = 0; 
    int isEnable = 1;
    int amountOfElementsOnPage = getAmountOfElementsOnPage(smenu);
    showMenu(&smenu->menu, 0);
    while(isEnable) {
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
            if(iItem > 0)
                iItem -= 1;
            else {
                if (smenu->page > 0) {
                    smenu->page--;
                    iItem = smenu->maxPoints-1;
                    updateScrollMenu(smenu);
                    amountOfElementsOnPage = getAmountOfElementsOnPage(smenu);
                }
            }
            showMenu(&smenu->menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(iItem < smenu->menu.pointsAmount-1)
                iItem += 1;
            else {
                if (smenu->page < smenu->bufferPointsAmount/smenu->maxPoints) {
                    smenu->page++;
                    iItem = 0;
                    updateScrollMenu(smenu);
                    amountOfElementsOnPage = getAmountOfElementsOnPage(smenu);
                }
            }
            showMenu(&smenu->menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            clearMenu(&smenu->menu);
            return iItem;
        }
        if(GetAsyncKeyState(VK_LEFT)) {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
            isEnable = 0;
            clearMenu(&smenu->menu);
            return -1;
        }
    }
}