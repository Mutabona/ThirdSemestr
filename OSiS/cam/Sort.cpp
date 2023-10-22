#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <windows.h>
#include <string>

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

string format_time(chrono::steady_clock::time_point time_point) {
	auto time_since_epoch = time_point.time_since_epoch();
	auto hours = chrono::duration_cast<chrono::hours>(time_since_epoch);
	time_since_epoch -= hours;
	auto minutes = chrono::duration_cast<chrono::minutes>(time_since_epoch);
	time_since_epoch -= minutes;
	auto seconds = chrono::duration_cast<chrono::seconds>(time_since_epoch);
	time_since_epoch -= seconds;
	auto milliseconds = chrono::duration_cast<chrono::milliseconds>(time_since_epoch);

	char buffer[12];
	sprintf_s(buffer, "%02d:%02d:%03d", static_cast<int>(minutes.count()), static_cast<int>(seconds.count()), static_cast<int>(milliseconds.count()));

	return string(buffer);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int N = 5400;
	const int num_trials = 100;

	vector<int> arr(N);
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 10000);

	auto t_start = chrono::steady_clock::now();
	cout << "Врмея начала Tstrt: " << format_time(t_start) << endl;
	// Запускаем цикл сортировки и замеряем время
	auto t1 = chrono::high_resolution_clock::now();

	for (int i = 0; i < num_trials; ++i) {
		// Заполняем массив случайными числами
		for (int& item : arr) item = distribution(generator);
		quickSort(arr, 0, N - 1);
	}

	auto t2 = chrono::steady_clock::now();

	// Вычисляем среднее время сортировки
	auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	double avg_time = static_cast<double>(duration) / num_trials;

	cout << "Среднее время одной сортировки: " << avg_time << " мс" << endl;

	auto t_end = chrono::high_resolution_clock::now();
	
	cout << "Время окончания Tend: " << format_time(t_end) << endl;

	return 0;
}