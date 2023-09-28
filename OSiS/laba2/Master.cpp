#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <clocale>
#include <string>

PROCESS_INFORMATION createProcess(int argc, TCHAR *argv[], int number, DWORD priority);

int main(int argc, TCHAR *argv[]) {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    DWORD priorities[] = {IDLE_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, IDLE_PRIORITY_CLASS, HIGH_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS};

    PROCESS_INFORMATION pinfo[2];

    for (int i = 0; i <= 2; i++) {
        pinfo[0] = createProcess(argc, argv, i, priorities[i*2]);
        pinfo[1] = createProcess(argc, argv, i, priorities[i*2+1]);
        WaitForSingleObject(pinfo[0].hProcess, INFINITE);
        WaitForSingleObject(pinfo[1].hProcess, INFINITE);
    }

    exit(0);
}

const TCHAR prioritiesNames[3][25] = { _T("NORMAL"), _T("IDLE"), _T("HIGH")};

PROCESS_INFORMATION createProcess(int argc, TCHAR *argv[], int number, DWORD priority) {

    STARTUPINFO sinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    TCHAR title[128];
    wsprintf(title, _T("Process: %d; Priority: %s"), number, prioritiesNames[priority/64]);
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
        wprintf( L"Процесс не создан (%d).\n", GetLastError()) ;
    }

    return pinfo;  
}