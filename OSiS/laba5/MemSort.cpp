#include <iostream>
#include <windows.h>
#include <ctime>
#include <limits.h>
#include <tchar.h>

SIZE_T dwSize = 4096;

TCHAR szName[]=TEXT("memshare");

int main() {
    printf("Hochu post");
    HANDLE mtx = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"memory");   
    if (mtx) WaitForSingleObject(mtx, INFINITE);
    else {
        printf("\nya daun\n");
    }

    printf("Posrt poluchil");

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

    printf("\n Sorted \n");

    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    printf("Posrt vernul");
    ReleaseMutex(mtx);   
    CloseHandle(mtx);
}