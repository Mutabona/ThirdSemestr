#include <iostream>
#include <windows.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <clocale>
#include "Array.cpp"


int main()
{ 
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    SYSTEMTIME Tstrt;
    GetSystemTime(&Tstrt);

    wprintf(L"Время начала: %02d:%02d:%003d\n", Tstrt.wMinute, Tstrt.wSecond, Tstrt.wMilliseconds);

    SYSTEMTIME t1;
    GetSystemTime(&t1);

    Array array(5000);

    for (int i = 0; i < 100; i++) {
        array.fill();
        array.sort();
    }

    SYSTEMTIME t2;
    GetSystemTime(&t2);

    float avgTime = (float)((((t2.wHour-t1.wHour)*60 + t2.wMinute-t1.wMinute)*60 + t2.wSecond-t1.wSecond)*1000 + t2.wMilliseconds - t1.wMilliseconds)/100;

    wprintf(L"Среднее время одной сортировки: %.3f ms\n", avgTime);

    SYSTEMTIME tend;
    GetSystemTime(&tend);

    wprintf(L"Время окончания программы: %02d:%02d:%003d\n", tend.wMinute, tend.wSecond, tend.wMilliseconds);

    Sleep(4000);
}