#include "scrollMenu.h"
#include "studentMenu.h"

struct scrollMenu* getScrollMenu(struct student* _buffer, int _pointsAmount, int _bufferPointsAmount, COORD _start, COORD _end, int _printStudentsMode) {
    struct scrollMenu *smenu = (struct scrollMenu*)malloc(sizeof(struct scrollMenu));
    int maxPoints = 15;
    smenu->page = 0;
    smenu->buffer = _buffer;
    smenu->bufferPointsAmount = _bufferPointsAmount;
    smenu->maxPoints = maxPoints;
    smenu->printStudentsMode = _printStudentsMode;

    WCHAR **points;
    points = (WCHAR**)malloc(maxPoints*sizeof(WCHAR*));
    for (int i = 0; i < maxPoints; i++) {
        points[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }

    smenu->menu = getMenu(_pointsAmount, _start, _end, points);

    return smenu;
}

void updateScrollMenu(struct scrollMenu* smenu) {
    clearMenu(smenu->menu);
    if (!smenu->buffer) {
        smenu->menu->points[0] = L"Нет таких студентов";
        smenu->menu->pointsAmount = 1;
        return;
    }
    int start = smenu->page * smenu->maxPoints;
    smenu->menu->pointsAmount = getAmountOfElementsOnPage(smenu);
    if (smenu->printStudentsMode == 0) {
        for(int i = 0; i < smenu->menu->pointsAmount; i++) {
            smenu->menu->points[i] = studentToString(smenu->buffer[start+i]);
        }
    }
    else {
        for(int i = 0; i < smenu->menu->pointsAmount; i++) {
            smenu->menu->points[i] = studentWithUnjustifiedHoursToString(smenu->buffer[start+i]);
        }
    }
}

int getAmountOfElementsOnPage(struct scrollMenu *smenu) {
    int amountOfElementsOnPage;
    if ((smenu->bufferPointsAmount - smenu->page * smenu->maxPoints)/smenu->maxPoints > 0) {
        amountOfElementsOnPage = smenu->maxPoints;
        smenu->menu->end.Y = smenu->menu->start.Y + amountOfElementsOnPage;
    }
    else {
        amountOfElementsOnPage = smenu->bufferPointsAmount - smenu->page * smenu->maxPoints;
        smenu->menu->end.Y = smenu->menu->start.Y + amountOfElementsOnPage;
    }
    return amountOfElementsOnPage;
}

int runScrollMenu(struct scrollMenu *smenu) {
    updateScrollMenu(smenu);
    int iItem = 0; 
    int isEnable = 1;
    printHeader(smenu);
    showMenu(smenu->menu, 0);
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
                }
            }
            showMenu(smenu->menu, iItem);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(iItem < smenu->menu->pointsAmount-1)
                iItem += 1;
            else {
                if (smenu->page < (smenu->bufferPointsAmount-1)/smenu->maxPoints) {
                    smenu->page++;
                    iItem = 0;
                    updateScrollMenu(smenu);
                }
            }
            showMenu(smenu->menu, iItem);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            clearMenu(smenu->menu);
            clearHeader(smenu);
            return iItem;
        }
        if(GetAsyncKeyState(VK_LEFT)) {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
            isEnable = 0;
            clearMenu(smenu->menu);
            clearHeader(smenu);
            return -1;
        }
    }
}

void printHeader(struct scrollMenu* smenu) {
    gotoxy(smenu->menu->start.X - 1, smenu->menu->start.Y - 3);
    wprintf(L"+");
    for (int i = smenu->menu->start.X + 1; i < smenu->menu->end.X + 2; i++) wprintf(L"-");
    wprintf(L"+");
    gotoxy(smenu->menu->start.X - 1, smenu->menu->start.Y - 2);
    if (smenu->printStudentsMode == 0) {
        wprintf(L"|  %6s|%7s|%31s|%11s|%4s|%10s|%10s |", L"Номер", L"Группа", L"ФИО", L"ДР", L"Пол", L"Пропустил", L"Оправдал");
    } else {
        wprintf(L"|  %6s|%7s|%31s|%20s|", L"Номер", L"Группа", L"ФИО", L"Неоправдано часов");
    }
}

void clearHeader(struct scrollMenu* smenu) {
    for (int y = smenu->menu->start.Y - 3; y < smenu->menu->end.Y + 1; y++) {
        gotoxy(smenu->menu->start.X - 1, y);
        for (int x = smenu->menu->start.X - 1; x < smenu->menu->end.X+2; x++) {
            wprintf(L" ");
        }
    }
}