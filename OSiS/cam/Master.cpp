#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>

using namespace std;

wchar_t* convertToLPCWSTR(const char* charArray) {
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	DWORD priorityClasses[3] = { IDLE_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, HIGH_PRIORITY_CLASS };
	int priorityPairs[3][2] = { { 0, 1 },{ 0, 2 },{ 1, 1 } };

	for (int i = 0; i < 3; ++i) {
		STARTUPINFO si1, si2;
		PROCESS_INFORMATION pi1, pi2;

		ZeroMemory(&si1, sizeof(si1));
		si1.cb = sizeof(si1);
		si1.dwFlags = STARTF_USESHOWWINDOW;
		si1.wShowWindow = SW_SHOW;
		ZeroMemory(&pi1, sizeof(pi1));

		ZeroMemory(&si2, sizeof(si2));
		si2.cb = sizeof(si2);
		si2.dwFlags = STARTF_USESHOWWINDOW;
		si2.wShowWindow = SW_SHOW;
		ZeroMemory(&pi2, sizeof(pi2));
		
		if (!CreateProcess(NULL, convertToLPCWSTR("Sort.exe"), NULL, NULL, FALSE, priorityClasses[priorityPairs[i][0]] | CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) {
			std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
			return -1;
		}
	
		if (!CreateProcess(NULL, convertToLPCWSTR("Sort.exe"), NULL, NULL, FALSE, priorityClasses[priorityPairs[i][1]] | CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
			std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
			return -1;
		}
		DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
		
		WaitForSingleObject(pi1.hProcess, 3000);
		WaitForSingleObject(pi2.hProcess, 3000);
		
	}
	system("pause");
	return 0;
}
