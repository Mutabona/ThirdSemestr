#include <iostream>
#include <windows.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <clocale>

class Array {
private:
    int* array;
    int size;

    void qsort(int start, int end) {
        if (start > end) return;

        int i = start;
        int j = start;

        int pivot = array[end];

        while (i <= end) {
            if (array[i] > pivot) {
                i++;
            }
            else {
                swap(i, j);
                i++;
                j++;
            }
        }

        int pos = j-1;

        qsort(start, pos-1);
        qsort(pos+1, end);
    }

    

public:
    Array(int _size): size(_size) {
        array = new int[size];
    }

    void sort() {
        qsort(0, size-1);
    }

    void fill() {
        srand(time(NULL));
        for(int i = 0; i < size; i++) {
            array[i] = rand()%10000;
        }
    }

    void swap(int pos1, int pos2) {
        int temp = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = temp;
    }

    void printArray() {
        for (int i = 0; i < size; i++)
            printf("%d ", array[i]);
        printf("\n");
    }

    ~Array() {
        delete[] array;
    }
};

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

    Sleep(2000);
}