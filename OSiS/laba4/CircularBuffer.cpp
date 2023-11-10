#include <iostream>
#include <windows.h>
#include <tchar.h>

class CircularBuffer {
    private:
    int* buffer;
    int size;
    int head;
    u_int count;
    int tail;
    HANDLE full;
    HANDLE empty;

    public:
    CircularBuffer(int _size = 9) {
        size = _size;
        buffer = new int[size];
        head = tail = 0;
        count = 0;
        empty = CreateSemaphore(NULL, size, size, _T("empty"));
        full = CreateSemaphore(NULL, 0, size, _T("full"));
    }

    void put(int number) {
        WaitForSingleObject(empty, INFINITE);
        HANDLE mtx = CreateMutex(NULL, TRUE, _T("input"));
        WaitForSingleObject(mtx, INFINITE);     
        buffer[tail] = number;
        tail = (tail+1) % size;
        count++;         
        ReleaseMutex(mtx);
        CloseHandle(mtx);
        ReleaseSemaphore(full, 1, NULL);
    }

    int get() {
        WaitForSingleObject(full, INFINITE);
        //HANDLE mtx = CreateMutex(NULL, TRUE, _T("output")); WaitForSingleObject(mtx, INFINITE); 
        int number = buffer[head];
        head = (head+1) % size;
        count--;
        //ReleaseMutex(mtx); CloseHandle(mtx);
        ReleaseSemaphore(empty, 1, NULL);
        return number;
    }

    int getCount() {
        return count;
    }

    ~CircularBuffer() {
        delete[] buffer;
        CloseHandle(empty);
        CloseHandle(full);
    }
};