#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <time.h>
#include "CircularBuffer.cpp"

const int MAX_THREADS = 2;
const int Nbuf = 9;
const int N = 450;

DWORD WINAPI createSequence( LPVOID lpParam ) {
    CircularBuffer *buffer = (CircularBuffer*)lpParam;

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        int number = rand()%100;
        buffer->put(number);
    }
    return 0;
}

DWORD WINAPI printSequence( LPVOID lpParam ) {
    CircularBuffer *buffer = (CircularBuffer*)lpParam;
    for (int i = 0; i < N; i++) {
        printf("C%d: %d ", buffer->getCount(), buffer->get());
    }
    return 0;
}

int main(int argc, TCHAR *argv[]) {
    CircularBuffer buffer(Nbuf);

    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS]; 

    hThreadArray[0] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            createSequence,       // thread function name
            &buffer,          // argument to thread function 
            CREATE_SUSPENDED,                      // use default creation flags 
            &dwThreadIdArray[0]);   // returns the thread identifier

    hThreadArray[1] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            printSequence,       // thread function name
            &buffer,          // argument to thread function 
            CREATE_SUSPENDED,                      // use default creation flags 
            &dwThreadIdArray[1]);   // returns the thread identifier

    SetThreadPriority(hThreadArray[0], THREAD_PRIORITY_IDLE);
    SetThreadPriority(hThreadArray[1], THREAD_PRIORITY_TIME_CRITICAL);
    ResumeThread(hThreadArray[1]);
    ResumeThread(hThreadArray[0]);

    for (int i = 0; i < MAX_THREADS; i++) {
        WaitForSingleObject(hThreadArray[i], INFINITE);
    }
}