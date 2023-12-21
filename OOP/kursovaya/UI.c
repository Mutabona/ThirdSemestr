#include "UI.h"



struct UI* getUI(struct studentService *studentService) {
    struct UI *ui = (struct UI*)malloc(sizeof(struct UI));

    ui->studentService = studentService;

    //Main menu
    int mainMenuPointsAmount = 7;

    COORD mainMenuStart, mainMenuEnd;
    mainMenuStart.X = 2; mainMenuStart.Y = 2;
    mainMenuEnd.X = mainMenuStart.X + 20; mainMenuEnd.Y = mainMenuStart.Y + mainMenuPointsAmount;

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
    mainMenuPoints[5] = L"Обработка студентов";
    mainMenuPoints[6] = L"Выход";

    ui->mainMenu = getMenu(
        mainMenuPointsAmount,
        mainMenuStart,
        mainMenuEnd,
        mainMenuPoints
    );

    printf("Main menu loaded\n");

    //Scroll menu
    int scrollMenuPointsAmount = 15;
    int scrollMenuBufferPointsAmount = studentService->studentsAmount;

    COORD scrollMenuStart, scrollMenuEnd;
    scrollMenuStart.X = mainMenuEnd.X + 2; scrollMenuStart.Y = 2;
    scrollMenuEnd.X = scrollMenuStart.X + 100; scrollMenuEnd.Y = scrollMenuStart.Y + scrollMenuPointsAmount;

    struct student* buffer = getAllStudents(studentService);
    printf("Scroll menu buffer filled\n");

    ui->scrollMenu = getScrollMenu (buffer,
                                    scrollMenuPointsAmount,
                                    scrollMenuBufferPointsAmount,
                                    scrollMenuStart,
                                    scrollMenuEnd,
                                    0
                                    );

    printf("Scroll menu loaded\n");

    //File menu
    int fileMenuPointsAmount = 4;

    COORD fileMenuStart = scrollMenuStart;
    COORD fileMenuEnd = scrollMenuEnd;

    WCHAR **fileMenuPoints;
    fileMenuPoints = (WCHAR**)malloc(fileMenuPointsAmount*sizeof(WCHAR*));
    for (int i = 0; i < fileMenuPointsAmount; i++) {
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

    printf("File menu loaded\n");

    //Bad students menu
    struct student* badBuffer = getStudentsWithUnjustifiedHours(studentService);
    int badStudentsMenuBufferPointsAmount = studentService->lastFoundStudentsAmount;
    printf("Bad students menu buffer filled\n");

    ui->badStudentsMenu = getScrollMenu (badBuffer,
                                    scrollMenuPointsAmount,
                                    badStudentsMenuBufferPointsAmount,
                                    scrollMenuStart,
                                    scrollMenuEnd,
                                    1
                                    );

    printf("Bad students menu loaded\n");

    hidecursor();
    return ui;
}

void runUI(struct UI *ui) {
    system("cls");
    
    while(initMainMenu(ui) != -1) {}
    freeUI(ui);
    return;
}

void freeUI(struct UI *ui) {
    for(int i = 0; i < ui->mainMenu->pointsAmount; i++) {
        free(ui->mainMenu->points[i]);
    }
    free(ui->mainMenu->points);
    for(int i = 0; i < ui->scrollMenu->menu->pointsAmount; i++) {
        free(ui->scrollMenu->menu->points[i]);
    }
    free(ui->scrollMenu->menu->points);
    free(ui->scrollMenu->buffer);
    for(int i = 0; i < ui->fileMenu->pointsAmount; i++) {
        free(ui->fileMenu->points[i]);
    }
    free(ui->fileMenu->points);
    for(int i = 0; i < ui->badStudentsMenu->menu->pointsAmount; i++) {
        free(ui->badStudentsMenu->menu->points[i]);
    }
    free(ui->badStudentsMenu->menu->points);
    free(ui->badStudentsMenu->buffer);
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
                }
                break;
            case 1:
                {
                struct student* students = findStudent(ui);
                if (!students) {
                    ui->scrollMenu->buffer = NULL;
                    ui->scrollMenu->bufferPointsAmount = 0;
                    runScrollMenu(ui->scrollMenu);
                } else {
                    ui->scrollMenu->buffer = students;
                    ui->scrollMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
                    int studentNumber = students[runScrollMenu(ui->scrollMenu)].number;
                    removeStudent(ui->studentService, studentNumber);
                }
                updateScrollBuffer(ui);
                }
                break;
            case 2:
                initScrollMenu(ui);
                updateScrollBuffer(ui);
                break;
            case 3: 
                {
                struct student* students = findStudent(ui);
                if (!students) {
                    ui->scrollMenu->buffer = NULL;
                    ui->scrollMenu->bufferPointsAmount = 0;
                    runScrollMenu(ui->scrollMenu);
                    break;
                }
                ui->scrollMenu->buffer = students;
                ui->scrollMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
                initScrollMenuForSearch(ui);
                }
                break;
            case 4:
                initFileMenu(ui);
                break;
            case 5:                
                initBadStudentsMenu(ui);
                break;
            case 6:
                return -1;
        }
    }
}

struct student* findStudent(struct UI* ui) {
    struct student* student = newStudent();
    struct studentMenu* studentMenu = getStudentMenu(student);
    int choice = runSubMenu(&studentMenu->menu);
    if (choice == -1) return NULL;
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

void updateBadBuffer(struct UI* ui) {
    ui->badStudentsMenu->buffer = getStudentsWithUnjustifiedHours(ui->studentService);
    ui->badStudentsMenu->bufferPointsAmount = ui->studentService->lastFoundStudentsAmount;
}

int initScrollMenu(struct UI* ui) {
    int choice;
    struct scrollMenu* smenu = ui->scrollMenu;
    updateScrollBuffer(ui);
    
    while ((choice = runScrollMenu(smenu)) != -1) {
        struct student* student = &smenu->buffer[choice+smenu->page*smenu->maxPoints];
        initStudentMenu(student);
        struct student* stud = getStudentByNumber(ui->studentService, student->number);
        *stud = *student;
    }
}

int initScrollMenuForSearch(struct UI* ui) {
    int choice;
    struct scrollMenu* smenu = ui->scrollMenu;
    
    while ((choice = runScrollMenu(smenu)) != -1) {
        struct student* student = &smenu->buffer[choice+smenu->page*smenu->maxPoints];
        initStudentMenu(student);
        struct student* stud = getStudentByNumber(ui->studentService, student->number);
        *stud = *student;
    }
}

int initBadStudentsMenu(struct UI* ui) {
    int choice;
    struct scrollMenu* smenu = ui->badStudentsMenu;
    updateBadBuffer(ui);
    gotoxy(ui->mainMenu->start.X, smenu->menu->end.Y + 2);
    wprintf(getStats(ui->studentService));
    
    while ((choice = runScrollMenu(smenu)) != -1) {
        struct student* student = &smenu->buffer[choice+smenu->page*smenu->maxPoints];
        initStudentMenu(student);
        struct student* stud = getStudentByNumber(ui->studentService, student->number);
        *stud = *student;
    }
    system("cls");
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
    switch (choice) {
        case 0:
        {
            char *fileName = getFileName(ui);
            sprintf(fileName, "%s.txt", fileName);
            saveStudentsToFile(ui->studentService, fileName);
            break;
        }
        case 1:
        {
            char *fileName = getFileName(ui);
            sprintf(fileName, "%s.dat", fileName);
            saveStudentsToBinaryFile(ui->studentService, fileName);
            break;
        }
        case 2:
        {
            char *fileName = getFileName(ui);
            sprintf(fileName, "%s.txt", fileName);
            loadStudentsFromFile(ui->studentService, fileName);
            updateScrollBuffer(ui);
            break;
        }
        case 3:
        {
            char *fileName = getFileName(ui);
            sprintf(fileName, "%s.dat", fileName);
            loadStudentsFromBinaryFile(ui->studentService, fileName);
            updateScrollBuffer(ui);
            break;
        }
    }
    clearMenu(ui->fileMenu);
}

char* getFileName(struct UI* ui) {
    gotoxy(ui->scrollMenu->menu->start.X, ui->scrollMenu->menu->start.Y);
    wprintf(L"Название файла: ");
    
    char* fileName = (char*)malloc(10*sizeof(char));
    while (!GetAsyncKeyState(VK_RETURN)) {
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        gotoxy(ui->scrollMenu->menu->start.X + 18, ui->scrollMenu->menu->start.Y);
        gets(fileName);
    }
    Sleep(500);
    return fileName;
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}