#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <tchar.h>

#include "UI.h"
#include "studentService.h"

int main() {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    struct studentService *studentService = getStudentService();
    struct UI *ui = getUI(studentService);
    runUI(ui);
    return 0;
}