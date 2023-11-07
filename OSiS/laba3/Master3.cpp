#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <string>
#include <io.h>
#include <clocale>

PROCESS_INFORMATION createProcess(int number);

int main(int argc, TCHAR *argv[]) {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    PROCESS_INFORMATION pinfo[2];

    HANDLE mtx = CreateMutex(NULL, FALSE, _T("console"));

    for (int i = 0; i <= 2; i++) {
        pinfo[i] = createProcess(i);
    }

    for (int i = 0; i <= 2; i++) {
        WaitForSingleObject(pinfo[i].hProcess, INFINITE);
    }

    ReleaseMutex(mtx);
    CloseHandle(mtx);

    exit(0);
}

PROCESS_INFORMATION createProcess(int number) {  

    STARTUPINFO sinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    
    PROCESS_INFORMATION pinfo;
    ZeroMemory(&pinfo, sizeof(pinfo));

    TCHAR cmd[128];
    int pid=GetCurrentProcessId();
    wsprintf(cmd, _T("%d"), pid);
    wsprintf(cmd + _tcslen(cmd), _T(" %d"), number);
    
    if( !CreateProcess( _T("Sort3.exe"),   // No module name (use command line)
        cmd,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        NORMAL_PRIORITY_CLASS,            // Creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &sinfo,            // Pointer to STARTUPINFO structure
        &pinfo )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        wprintf( L"Процесс не создан (%d).\n", GetLastError()) ;
    }

    return pinfo;  
}