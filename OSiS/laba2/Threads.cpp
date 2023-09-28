#include <iostream>
#include <tchar.h>
#include <windows.h>
#include "Array.cpp"

const int N = 100;
const int MAX_THREADS = 2;

DWORD WINAPI sort( LPVOID lpParam ) {
    Array* array = (Array*)lpParam;
    array->sort();
    return 0;
}

DWORD WINAPI printMass( LPVOID lpParam ) {
    Array* array = (Array*)lpParam;
    array->printArray();
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
            sort,       // thread function name
            &array,          // argument to thread function 
            CREATE_SUSPENDED,                      // use default creation flags 
            &dwThreadIdArray[0]);   // returns the thread identifier 
    
    hThreadArray[1] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            printMass,       // thread function name
            &array,          // argument to thread function 
            CREATE_SUSPENDED,                      // use default creation flags 
            &dwThreadIdArray[1]);   // returns the thread identifier 


    SetThreadPriority(hThreadArray[0], THREAD_PRIORITY_TIME_CRITICAL);
    SetThreadPriority(hThreadArray[1], THREAD_PRIORITY_LOWEST);
    ResumeThread(hThreadArray[0]);
    ResumeThread(hThreadArray[1]);

    DWORD exitCodes[2];

    do {
        GetExitCodeThread(hThreadArray[0], &exitCodes[0]);
        GetExitCodeThread(hThreadArray[1], &exitCodes[1]);
        Sleep(500);
    } while (exitCodes[0] == STILL_ACTIVE || exitCodes[1] == STILL_ACTIVE);
}