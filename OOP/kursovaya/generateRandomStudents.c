#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// Структура для хранения данных студента
#include "student.h"

// Функция для генерации случайной строки из заданного набора символов
WCHAR* random_string(WCHAR* set, int length) {
    WCHAR* result = (WCHAR*)malloc((length + 1) * sizeof(WCHAR)); // Выделяем память для результата
    int set_length = wcslen(set); // Определяем длину набора символов
    for (int i = 0; i < length; i++) {
        int index = rand() % set_length; // Генерируем случайный индекс из диапазона [0, set_length - 1]
        result[i] = set[index]; // Копируем символ из набора по индексу в результат
    }
    result[length] = L'\0'; // Добавляем нулевой символ в конец строки
    return result; // Возвращаем результат
}

// Функция для генерации случайной даты в формате dd.mm.yyyy
WCHAR* random_date() {
    WCHAR* result = (WCHAR*)malloc(11 * sizeof(WCHAR)); // Выделяем память для результата
    int day = rand() % 31 + 1; // Генерируем случайный день от 1 до 31
    int month = rand() % 12 + 1; // Генерируем случайный месяц от 1 до 12
    int year = rand() % 23 + 2000; // Генерируем случайный год от 2000 до 2020
    wsprintfW(result, L"Aboba"); // Форматируем дату в строку
    return result; // Возвращаем результат
}

// Функция для генерации случайной записи студента
struct student random_student() {
    struct student result; // Объявляем переменную для результата
    result.number = rand() % 100 + 1; // Генерируем случайный номер от 1 до 100
    wcscpy(result.group, random_string(L"ABCD", 2)); // Генерируем случайную группу из двух букв
    wcscat(result.group, random_string(L"0123456789", 3)); // Добавляем к группе три цифры
    wcscpy(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // Генерируем случайную фамилию из одной заглавной буквы
    wcscat(result.FIO, random_string(L"abcdefghijklmnopqrstuvwxyz", rand() % 10 + 3)); // Добавляем к фамилии от 3 до 12 строчных букв
    wcscat(result.FIO, L" "); // Добавляем пробел
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // Генерируем случайное имя из одной заглавной буквы
    wcscat(result.FIO, L"."); // Добавляем точку
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // Генерируем случайное отчество из одной заглавной буквы
    wcscat(result.FIO, L"."); // Добавляем точку
    wcscpy(result.birthday, random_date()); // Генерируем случайную дату рождения
    result.gender = rand() % 2; // Генерируем случайный пол: 0 - мужской, 1 - женский
    result.missedHours = rand() % 100; // Генерируем случайное количество пропущенных часов от 0 до 99
    result.justifiedHours = rand() % (result.missedHours + 1); // Генерируем случайное количество оправданных часов от 0 до пропущенных часов
    return result; // Возвращаем результат
}

// Главная функция программы
struct student* generateStudents(int amount) {
    srand(time(NULL)); // Инициализируем генератор случайных чисел
    struct student* students = (struct student*)malloc(amount*sizeof(struct student)); // Объявляем массив из 10 студентов
    for (int i = 0; i < amount; i++) {
        students[i] = random_student(); // Генерируем случайную запись студента и сохраняем в массив
    }
    return students; // Завершаем программу
}