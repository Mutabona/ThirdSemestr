#include "UI.h"



struct UI* getUI(struct studentService *studentService) {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    int scrollMenuPointsAmount = 15;
    int scrollMenuBufferPointsAmount = studentService->studentsAmount;

    COORD scrollMenuStart, scrollMenuEnd;
    scrollMenuStart.X = 15; scrollMenuStart.Y = 2;
    scrollMenuEnd.X = 113; scrollMenuEnd.Y = 17;

    struct student* buffer = getAllStudents(studentService);

    ui->scrollMenu = getScrollMenu(buffer,
                                       scrollMenuPointsAmount,
                                       scrollMenuBufferPointsAmount,
                                       scrollMenuStart,
                                       scrollMenuEnd
                                       );

    int mainMenuPointsAmount = 4;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = 14; mainMenuEnd.Y = 17;

    WCHAR **mainMenuPoints;
    mainMenuPoints = (WCHAR**)malloc(mainMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        mainMenuPoints[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }
    mainMenuPoints[0] = L"Добавить";
    mainMenuPoints[1] = L"Убрать";
    mainMenuPoints[2] = L"Вывести";
    mainMenuPoints[3] = L"Kukaracha";

    ui->mainMenu = getMenu(
        mainMenuPointsAmount,
        mainMenuStart,
        mainMenuEnd,
        mainMenuPoints
    );

    //hidecursor();

    return ui;
}

void runUI(struct UI *ui) {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    //system("cls");

    //printBorders();
    
    initMainMenu(ui);
}

int initMainMenu(struct UI* ui) {
    int choice;
    while ((choice = runMenu(ui->mainMenu)) != -1) {
        switch(choice) {
            case 0:
                break;
            case 2:
                initScrollMenu(ui);
                break;
        }
    }
}

int initScrollMenu(struct UI* ui) {
    int choice;
    struct scrollMenu* smenu = ui->scrollMenu;
    while ((choice = runScrollMenu(ui->scrollMenu)) != -1) {
        initStudentMenu(ui, choice);
    }
}

int initStudentMenu(struct UI* ui, int item) {
    int choice;
    struct scrollMenu* smenu = ui->scrollMenu;
    struct studentMenu* studentMenu = getStudentMenu(&smenu->buffer[item+smenu->page*smenu->maxPoints]);
    showMenu(&studentMenu->menu, item);
    while ((choice = runSubMenu(&studentMenu->menu)) != -1) {
        changeStudentMenu(studentMenu, choice);
    }
}

void printBorders() {
    home();
	wprintf(L"");
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}