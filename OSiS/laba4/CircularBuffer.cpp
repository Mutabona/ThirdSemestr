#include <iostream>
#include <windows.h>
#include <tchar.h>

class CircularBuffer {
    private:
    int* buffer;
    int size;
    int head;
    int tail;
    HANDLE semaphore;

    public:
    CircularBuffer(int _size = 9) {
        size = _size;
        buffer = new int[size];
        head = tail = 0;
        semaphore = CreateSemaphore(NULL, size, size, _T("buffer"));
    }

    void put(int number) {
        WaitForSingleObject(semaphore, INFINITE);      
        buffer[tail] = number;
        tail = (tail+1) % size;
    }

    int get() {
        while(!ReleaseSemaphore(semaphore, 1, NULL)) {}
        int number = buffer[head];
        head = (head+1) % size;
        return number;
    }

    ~CircularBuffer() {
        delete[] buffer;
        CloseHandle(semaphore);
    }
};