#include <iostream>
#include <windows.h>
#include <ctime>
#include <limits.h>
#include <tchar.h>

PROCESS_INFORMATION createProcess(TCHAR* pName);

int main() {
    HANDLE mtx = CreateMutexW(NULL, FALSE, L"memory");
    if (!mtx) printf("\nya churka\n");
    PROCESS_INFORMATION pinfo[2];
    pinfo[0] = createProcess(_T("MemShare.exe"));
    pinfo[1] = createProcess(_T("MemSort.exe"));
    WaitForSingleObject(pinfo[0].hProcess, INFINITE);
    WaitForSingleObject(pinfo[1].hProcess, INFINITE);
}

PROCESS_INFORMATION createProcess(TCHAR* pName) {  

    STARTUPINFO sinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    
    PROCESS_INFORMATION pinfo;
    ZeroMemory(&pinfo, sizeof(pinfo));

    TCHAR cmd[128];
    int pid=GetCurrentProcessId();
    wsprintf(cmd, _T("%d"), pid);
    
    CreateProcess( pName,   // No module name (use command line)
        cmd,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        NORMAL_PRIORITY_CLASS,            // Creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &sinfo,            // Pointer to STARTUPINFO structure
        &pinfo );           // Pointer to PROCESS_INFORMATION structure

    return pinfo;  
}