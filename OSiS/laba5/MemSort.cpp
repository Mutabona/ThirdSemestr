#include <iostream>
#include <windows.h>
#include <ctime>
#include <limits.h>
#include <tchar.h>

SIZE_T dwSize = 4096;

TCHAR szName[]=TEXT("memshare");

int main() {
    HANDLE mtx = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"memory");   
    if (mtx) WaitForSingleObject(mtx, INFINITE);
    else {
        printf("no work\n");
    }


    HANDLE hMapFile;
    short* sharedMemory;

    hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   szName);               // name of mapping object
    
    
    if (!hMapFile) printf("\n! hMapFile\n");

    sharedMemory = (short*)MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,  // read/write permission
               0,
               0,
               dwSize);


    if (!sharedMemory) printf("\n! sharedMemory\n");

<<<<<<< HEAD
    for (int i = 0; i < dwSize/sizeof(char)-2; i++) {
        printf("\n! nihuya ne rabotaet\n");
        for (int j = i; j < dwSize/sizeof(char)-1; j++) {
            if (sharedMemory[j] < sharedMemory[j+1]) {
                short temp = sharedMemory[j+1];
                sharedMemory[j+1] = sharedMemory[j];
                sharedMemory[j] = temp; 
            }
        }
    }
=======
    int i, key, j;
    for (i = 1; i < dwSize/sizeof(short); i++) {
        key = sharedMemory[i];
        j = i - 1;
>>>>>>> e6dee780dacdd0922d6610e1beefa51959d15457

        while (j >= 0 && sharedMemory[j] > key) {
            sharedMemory[j + 1] = sharedMemory[j];
            j = j - 1;
        }
        sharedMemory[j + 1] = key;
    }

    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    ReleaseMutex(mtx);   
    CloseHandle(mtx);
}