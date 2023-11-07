#include <iostream>
#include <tchar.h>
#include <windows.h>
#include "Array.cpp"

CRITICAL_SECTION CriticalSection; 

#define MAX_THREADS 3
#define N 80

DWORD WINAPI sort( LPVOID lpParam ) {
    Array array(N);
    array.sort();
    EnterCriticalSection(&CriticalSection);
    printf("N%d entered the critical section\n", *((int*)lpParam));
    array.printArray(*((int*)lpParam));
    LeaveCriticalSection(&CriticalSection);
    printf("N%d left the critical section\n", *((int*)lpParam));
    return 0;
}

int main(int argc, TCHAR *argv[]) {
    int threadNumberArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS]; 

    InitializeCriticalSection(&CriticalSection);

    for (int i = 0; i < MAX_THREADS; i++) {
        threadNumberArray[i] = i;
        hThreadArray[i] = CreateThread( 
                NULL,                   // default security attributes
                0,                      // use default stack size  
                sort,       // thread function name
                &threadNumberArray[i],          // argument to thread function 
                0,                      // use default creation flags 
                &dwThreadIdArray[i]);   // returns the thread identifier
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        WaitForSingleObject(hThreadArray[i], INFINITE);
    }

    DeleteCriticalSection(&CriticalSection);
}