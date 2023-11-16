#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <tchar.h>

#include "UI.c"

int main() {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    struct UI *ui = getUI();
    runUI(ui);
    return 0;
}