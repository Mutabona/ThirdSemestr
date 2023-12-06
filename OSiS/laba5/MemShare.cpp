#include <iostream>
#include <windows.h>
#include <ctime>
#include <limits.h>
#include <tchar.h>

SIZE_T dwSize = 4096;

TCHAR szName[]=TEXT("memshare");

int main() {
    HANDLE mtx = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"memory");
    printf("Posrt prinyal");
    
    if (mtx) WaitForSingleObject(mtx, INFINITE);
    else {
        printf("\nya govnoed\n");
    }

    srand ( time(0) );

    short* memory = (short*)VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < dwSize/sizeof(short); i++) {
        memory[i] = rand() % SHRT_MAX;
    }

    DWORD oldProt;
    VirtualProtect(memory, dwSize, PAGE_READONLY, &oldProt);

    HANDLE hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 dwSize,                // maximum object size (low-order DWORD)
                 szName);                 // name of mapping object


    short* sharedMemory = (short*)MapViewOfFile(hMapFile,   // handle to map object
                            FILE_MAP_ALL_ACCESS, // read/write permission
                            0,
                            0,
                            dwSize);

    CopyMemory(sharedMemory, memory, dwSize);
  
    printf("Posrt sdal");
    ReleaseMutex(mtx);
    CloseHandle(mtx);

    Sleep(1000);

    mtx = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"memory");
    printf("Posrt prinyal");
    
    if (mtx) WaitForSingleObject(mtx, INFINITE);
    else {
        printf("\nya govnoed\n");
    }

    VirtualProtect(memory, dwSize, PAGE_READWRITE, &oldProt);

    CopyMemory(memory, sharedMemory, dwSize);

    /*for (int i = 0; i < dwSize/sizeof(short); i++) {
        printf("%d ", memory[i]);
    }*/

    VirtualFree(memory, dwSize, MEM_RELEASE);
    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    ReleaseMutex(mtx);
    CloseHandle(mtx);
}