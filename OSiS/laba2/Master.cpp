#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <clocale>

void createProcess(int argc, TCHAR *argv[], int number, long priority);

int main(int argc, TCHAR *argv[]) {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    for (int i = 0; i < 3; i++) {
        for (int k = 1; k < 3; k++) {
            createProcess(argc, argv, k, NORMAL_PRIORITY_CLASS);
        }
    }

    exit(0);
}

void createProcess(int argc, TCHAR *argv[], int number, long priority) {
    STARTUPINFO sinfo;

    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    TCHAR title[128];
    wsprintf(title, _T("Process: %d; Priority: %d"), number, priority);
    sinfo.lpTitle = title;

    TCHAR cmd[128];

    if (argc!=1) _tcscpy(cmd, argv[1]);
    else _tcscpy(cmd, _T("Sort.exe"));

    PROCESS_INFORMATION pinfo;
    ZeroMemory(&pinfo, sizeof(pinfo));

    int pid=GetCurrentProcessId();
    
    wsprintf(cmd+_tcslen(cmd), _T(" %d"), pid);
    
    if( !CreateProcess( NULL,   // No module name (use command line)
        cmd,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        priority | CREATE_NEW_CONSOLE,            // Creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &sinfo,            // Pointer to STARTUPINFO structure
        &pinfo )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        wprintf( L"CreateProcess failed (%d).\n", GetLastError()) ;
        return;
    }

    WaitForSingleObject(pinfo.hProcess, INFINITE);
}