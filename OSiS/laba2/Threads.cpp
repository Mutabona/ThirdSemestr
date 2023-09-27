#include <iostream>
#include <tchar.h>
#include <windows.h>
#include "Array.cpp"

#define N 5
#define MAX_THREADS 3

DWORD WINAPI qsort( LPVOID lpParam ) {
    Array* array = (Array*)lpParam;
    array->sort();
    return 0;
}

int main(int argc, TCHAR *argv[]) {

    Array array(N);
    array.fill();

    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS]; 

    hThreadArray[0] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            qsort,       // thread function name
            &array,          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[0]);   // returns the thread identifier 


    Sleep(10000);
    array.printArray();
}