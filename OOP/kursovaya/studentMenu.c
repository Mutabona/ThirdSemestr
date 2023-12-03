#include "studentMenu.h"

struct studentMenu* getStudentMenu(struct student *_student) {
    struct studentMenu *menu = (struct studentMenu*)malloc(sizeof(struct studentMenu));
    menu->menu.choice = 0;
    menu->menu.pointsAmount = 7;
    COORD start, end;
    start.X = 23; start.Y = 2;
    end.X = 123; end.Y = 12;
    menu->menu.start = start;
    menu->menu.end = end;

    menu->student = _student;

    WCHAR **points;
    points = (WCHAR**)malloc(menu->menu.pointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < menu->menu.pointsAmount; i++) {
        points[i] = (WCHAR*)malloc(50*sizeof(WCHAR));
    }
    menu->menu.points = points;
    
    updateStudentMenu(menu);
    
    return menu;
}

void changeStudentMenu(struct studentMenu* menu, int item) {
    clearMenu(&menu->menu);
    switch(item) {
        case 0:
            //wsprintfW(menu->menu.points[0], L"Номер: ");
            break;

        case 1:
            wsprintfW(menu->menu.points[1], L"Группа: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR group[6];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(group);
            }
            wcscpy(menu->student->group, group);
            updateStudentMenu(menu);
            break;

        case 2:
            wsprintfW(menu->menu.points[2], L"ФИО: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR FIO[30];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(FIO);
            }
            wcscpy(menu->student->FIO, FIO);
            updateStudentMenu(menu);      
            break;
            
        case 3:
            wsprintfW(menu->menu.points[3], L"Дата рождения: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR birthday[11];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(birthday);
            }
            wcscpy(menu->student->birthday, birthday);
            updateStudentMenu(menu);
            break;

        case 4:
            wsprintfW(menu->menu.points[4], L"Пол: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR gender[2];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(gender);
            }
            menu->student->gender = _wtoi(gender);
            updateStudentMenu(menu);
            break;

        case 5:
            wsprintfW(menu->menu.points[5], L"Пропущено часов: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR missedHours[10];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(missedHours);
            }
            menu->student->missedHours = _wtoi(missedHours);
            updateStudentMenu(menu);
            break;
            
        case 6:
            wsprintfW(menu->menu.points[6], L"Оправдано часов: ");
            clearMenu(&menu->menu);
            showMenu(&menu->menu, item);
            gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
            
            WCHAR justifiedHours[10];
            while (!GetAsyncKeyState(VK_RETURN)) {
                gotoxy(menu->menu.start.X + 19, menu->menu.start.Y + item);
                _getws(justifiedHours);
            }
            menu->student->justifiedHours = _wtoi(justifiedHours);
            updateStudentMenu(menu);
            break;
    }
}

void updateStudentMenu(struct studentMenu* menu) {
    wsprintfW(menu->menu.points[0], L"Номер:           %d", menu->student->number);
    wsprintfW(menu->menu.points[1], L"Группа:          %s", menu->student->group);
    wsprintfW(menu->menu.points[2], L"ФИО:             %s", menu->student->FIO);
    wsprintfW(menu->menu.points[3], L"Дата рождения:   %s", menu->student->birthday);
    wsprintfW(menu->menu.points[4], L"Пол:             %d", menu->student->gender);
    wsprintfW(menu->menu.points[5], L"Пропущено часов: %d", menu->student->missedHours);
    wsprintfW(menu->menu.points[6], L"Оправдано часов: %d", menu->student->justifiedHours);
    clearMenu(&menu->menu);
}