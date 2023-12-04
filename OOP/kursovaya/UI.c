#include "UI.h"



struct UI* getUI(struct studentService *studentService) {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    ui->studentService = studentService;

    //Scroll menu
    int scrollMenuPointsAmount = 15;
    int scrollMenuBufferPointsAmount = studentService->studentsAmount;

    COORD scrollMenuStart, scrollMenuEnd;
    scrollMenuStart.X = 23; scrollMenuStart.Y = 2;
    scrollMenuEnd.X = 123; scrollMenuEnd.Y = scrollMenuStart.Y + scrollMenuPointsAmount;

    struct student* buffer = getAllStudents(studentService);

    ui->scrollMenu = getScrollMenu (buffer,
                                    scrollMenuPointsAmount,
                                    scrollMenuBufferPointsAmount,
                                    scrollMenuStart,
                                    scrollMenuEnd
                                    );


    //Main menu
    int mainMenuPointsAmount = 9;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = 22; mainMenuEnd.Y = mainMenuStart.Y + mainMenuPointsAmount;

    WCHAR **mainMenuPoints;
    mainMenuPoints = (WCHAR**)malloc(mainMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        mainMenuPoints[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }
    mainMenuPoints[0] = L"Добавить";
    mainMenuPoints[1] = L"Удалить";
    mainMenuPoints[2] = L"Вывести";
    mainMenuPoints[3] = L"Поиск";
    mainMenuPoints[4] = L"Файлы";
    mainMenuPoints[5] = L"Первая обработка";
    mainMenuPoints[6] = L"Вторая обработка";
    mainMenuPoints[7] = L"Третья обработка";
    mainMenuPoints[8] = L"Выход";

    ui->mainMenu = getMenu(
        mainMenuPointsAmount,
        mainMenuStart,
        mainMenuEnd,
        mainMenuPoints
    );

    //File menu
    int fileMenuPointsAmount = 4;

    COORD fileMenuStart = scrollMenuStart;
    COORD fileMenuEnd = scrollMenuEnd;

    WCHAR **fileMenuPoints;
    fileMenuPoints = (WCHAR**)malloc(fileMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < mainMenuPointsAmount; i++) {
        fileMenuPoints[i] = (WCHAR*)malloc(15*sizeof(WCHAR));
    }
    fileMenuPoints[0] = L"Сохранить в обычный файл";
    fileMenuPoints[1] = L"Сохранить в бинарный файл";
    fileMenuPoints[2] = L"Загрузить из обычного файла";
    fileMenuPoints[3] = L"Загрузить из бинарного файла";

    ui->fileMenu = getMenu(
        fileMenuPointsAmount,
        fileMenuStart,
        fileMenuEnd,
        fileMenuPoints
    );

    hidecursor();

    return ui;
}

void runUI(struct UI *ui) {
    // SetConsoleCP(1251);
	// SetConsoleOutputCP(1251);
    // setlocale(LC_ALL, "Russian");

    system("cls");
    system("doskey /listsize=0");

    //printBorders();
    
    while(initMainMenu(ui) != -1) {}
    return;
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
                free(student);
                }
                break;
            case 1:
                {
                struct student* students = findStudent(ui);
                ui->scrollMenu->buffer = students;
                ui->scrollMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
                int studentNumber = students[runScrollMenu(ui->scrollMenu)].number;
                removeStudent(ui->studentService, studentNumber);
                updateScrollBuffer(ui);
                }
                break;
            case 2:
                initScrollMenu(ui);
                break;
            case 3: 
                {
                struct student* students = findStudent(ui);
                ui->scrollMenu->buffer = students;
                ui->scrollMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
                initScrollMenu(ui);
                updateScrollBuffer(ui);
                }
                break;
            case 4:
                initFileMenu(ui);
                break;
            case 8:
                return -1;
        }
    }
}

struct student* findStudent(struct UI* ui) {
    struct student* student = newStudent();
    struct studentMenu* studentMenu = getStudentMenu(student);
    int choice = runSubMenu(&studentMenu->menu);
    changeStudentMenu(studentMenu, choice);
    struct student* students;
    switch (choice) {
        case 0:
            students = getStudentByNumber(ui->studentService, student->number);
            break;
        case 1:
            students = getStudentsByGroup(ui->studentService, student->group);
            break;
        case 2:
            students = getStudentsByFIO(ui->studentService, student->FIO);
            break;
        case 3:
            students = getStudentsByBirthday(ui->studentService, student->birthday);
            break;
        case 4:
            students = getStudentsByGender(ui->studentService, student->gender);
            break;
        case 5:
            students = getStudentsByMissedHours(ui->studentService, student->missedHours);
            break;
        case 6:
            students = getStudentsByJustifiedHours(ui->studentService, student->justifiedHours);
            break;
    }
    return students;
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

int initFileMenu(struct UI* ui) {
    int choice;
    choice = runSubMenu(ui->fileMenu);
    char *fileName = getFileName(ui);
    switch (choice) {
        case 0:
            sprintf(fileName, "%s.txt", fileName);
            saveStudentsToFile(ui->studentService, fileName);
            break;
        case 1:
            sprintf(fileName, "%s.dat", fileName);
            saveStudentsToBinaryFile(ui->studentService, fileName);
            break;
        case 2:
            sprintf(fileName, "%s.txt", fileName);
            loadStudentsFromFile(ui->studentService, fileName);
            updateScrollBuffer(ui);
            break;
        case 3:
            sprintf(fileName, "%s.dat", fileName);
            loadStudentsFromBinaryFile(ui->studentService, fileName);
            updateScrollBuffer(ui);
            break;
    }
    clearMenu(ui->fileMenu);
}

char* getFileName(struct UI* ui) {
    gotoxy(ui->scrollMenu->menu.start.X, ui->scrollMenu->menu.start.Y);
    wprintf(L"Название файла: ");
    
    char* fileName = (char*)malloc(10*sizeof(char));
    while (!GetAsyncKeyState(VK_RETURN)) {
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        gotoxy(ui->scrollMenu->menu.start.X + 18, ui->scrollMenu->menu.start.Y);
        gets(fileName);
    }
    return fileName;
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