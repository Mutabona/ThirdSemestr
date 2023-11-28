#include "studentMenu.h"

struct studentMenu* getStudentMenu(struct student *student) {
    struct studentMenu *menu = (struct studentMenu*)malloc(sizeof(struct studentMenu));
    menu->menu.choice = 0;
    menu->menu.pointsAmount = 7;
    COORD start, end;
    start.X = 15; start.Y = 2;
    end.X = 113; end.Y = 17;
    menu->menu.start = start;
    menu->menu.end = end;

    WCHAR **points;
    points = (WCHAR**)malloc(menu->menu.pointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < menu->menu.pointsAmount; i++) {
        points[i] = (WCHAR*)malloc(128*sizeof(WCHAR));
    }
    wsprintfW(points[0], L"Номер: %d", student->number);
    wsprintfW(points[1], L"Группа: %s", student->group);
    wsprintfW(points[2], L"ФИО: %s", student->FIO);
    wsprintfW(points[3], L"Дата рождения: %s", student->birthday);
    wsprintfW(points[4], L"Пол: %d", student->gender);
    wsprintfW(points[5], L"Пропущено часов: %d", student->missedHours);
    wsprintfW(points[6], L"Оправдано часов: %d", student->justifiedHours);
    

    menu->menu.points = points;
    return menu;
}

int runStudentMenu(struct student *student) {
    int item = 0;
    struct studentMenu* studentMenu = getStudentMenu(student);
    showMenu(&studentMenu->menu, item);
    int choice = runSubMenu(&studentMenu->menu);

    return choice;
}

void updateStudentMenu(struct studentMenu* studentMenu, int item) {
    switch(item) {
        
    }
}