
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <windows.h>

using namespace std;

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(vector<int>& arr, int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] >= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void printArray(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}

DWORD WINAPI sort(LPVOID lpParam) {
	vector<int>& arr = *(vector<int>*)lpParam;
	quickSort(arr, 0, arr.size() - 1);
	return 0;
}

DWORD WINAPI mass_print(LPVOID lpParam) {
	vector<int>& arr = *(vector<int>*)lpParam;
	printArray(arr);
	return 0;
}

int main() {
	const int N = 5400;
	vector<int> arr(N / 50);

	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 10000);
	for (int& item : arr) item = distribution(generator);
	
	DWORD dwThreadIdArray[2];
	HANDLE hThreadArray[2];

	hThreadArray[0] = CreateThread(NULL, 0, sort, &arr, CREATE_SUSPENDED, &dwThreadIdArray[0]);
	hThreadArray[1] = CreateThread(NULL, 0, mass_print, &arr, CREATE_SUSPENDED, &dwThreadIdArray[1]);

	SetThreadPriority(hThreadArray[0], THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hThreadArray[1], THREAD_PRIORITY_NORMAL);

	ResumeThread(hThreadArray[0]);
	ResumeThread(hThreadArray[1]);

	WaitForMultipleObjects(2, hThreadArray, TRUE, INFINITE);

	CloseHandle(hThreadArray[0]);
	CloseHandle(hThreadArray[1]);

	return 0;
}