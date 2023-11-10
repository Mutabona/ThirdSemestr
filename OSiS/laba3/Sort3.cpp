#include <iostream>
#include <windows.h>
#include <tchar.h>
#include "Array.cpp"

const int N = 80;

int main(int argc, TCHAR *argv[]) {
    //HANDLE mtx = OpenMutex(MUTEX_ALL_ACCESS, TRUE, _T("console"));
    
    //if (mtx) WaitForSingleObject(mtx, INFINITE);

    Array array(N);
    array.sort();

    for (int j = 0; j < N; j++) {
        printf("N%s: %d ", argv[1], array[j]);
    }

    printf("\n\n");

    //ReleaseMutex(mtx);
    //CloseHandle(mtx);
}