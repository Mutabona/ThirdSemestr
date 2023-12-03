#include "UI.h"



struct UI* getUI(struct studentService *studentService) {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    ui->studentService = studentService;

    int scrollMenuPointsAmount = 15;
    int scrollMenuBufferPointsAmount = studentService->studentsAmount;

    COORD scrollMenuStart, scrollMenuEnd;
    scrollMenuStart.X = 23; scrollMenuStart.Y = 2;
    scrollMenuEnd.X = 123; scrollMenuEnd.Y = 17;

    struct student* buffer = getAllStudents(studentService);

    ui->scrollMenu = getScrollMenu (buffer,
                                    scrollMenuPointsAmount,
                                    scrollMenuBufferPointsAmount,
                                    scrollMenuStart,
                                    scrollMenuEnd
                                    );

    int mainMenuPointsAmount = 10;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = 22; mainMenuEnd.Y = 17;

    WCHAR **mainMenuPoints;
    mainMenuPoints = (WCHAR**)malloc(mainMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        mainMenuPoints[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }
    mainMenuPoints[0] = L"Добавить";
    mainMenuPoints[1] = L"Удалить";
    mainMenuPoints[2] = L"Вывести";
    mainMenuPoints[3] = L"Поиск";
    mainMenuPoints[4] = L"Сохранить в файл";
    mainMenuPoints[5] = L"Загрузить из файла";
    mainMenuPoints[6] = L"Первая обработка";
    mainMenuPoints[7] = L"Вторая обработка";
    mainMenuPoints[8] = L"Третья обработка";
    mainMenuPoints[9] = L"Выход";

    ui->mainMenu = getMenu(
        mainMenuPointsAmount,
        mainMenuStart,
        mainMenuEnd,
        mainMenuPoints
    );

    hidecursor();

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
                {
                struct student* student = newStudent();
                initStudentMenu(student);
                addStudent(ui->studentService, *student);
                updateScrollBuffer(ui);
                }
                break;
            case 2:
                initScrollMenu(ui);
                break;
            case 3:
                findStudent(ui);
                break;
        }
    }
}

void findStudent(struct UI* ui) {
    struct student* student = newStudent();
    struct studentMenu* studentMenu = getStudentMenu(student);
    int choice = runSubMenu(&studentMenu->menu);
    changeStudentMenu(studentMenu, choice);
    struct student* students;
    switch (choice) {
        case 2:
            students = getStudentsByFIO(ui->studentService, student->FIO);
            break;
    }
    ui->scrollMenu->buffer = students;
    ui->scrollMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
    initScrollMenu(ui);
    updateScrollBuffer(ui);
}

void updateScrollBuffer(struct UI* ui) {
    ui->scrollMenu->buffer = getAllStudents(ui->studentService);
    ui->scrollMenu->bufferPointsAmount = ui->studentService->studentsAmount;
}

int initScrollMenu(struct UI* ui) {
    int choice;
    struct scrollMenu* smenu = ui->scrollMenu;
    
    while ((choice = runScrollMenu(ui->scrollMenu)) != -1) {
        struct student* student = &smenu->buffer[choice+smenu->page*smenu->maxPoints];
        initStudentMenu(student);
    }
}

int initStudentMenu(struct student* student) {
    int choice;
    struct studentMenu* studentMenu = getStudentMenu(student);
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