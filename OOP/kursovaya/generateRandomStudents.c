#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// ��������� ��� �������� ������ ��������
#include "student.h"

// ������� ��� ��������� ��������� ������ �� ��������� ������ ��������
WCHAR* random_string(WCHAR* set, int length) {
    WCHAR* result = (WCHAR*)malloc((length + 1) * sizeof(WCHAR)); // �������� ������ ��� ����������
    int set_length = wcslen(set); // ���������� ����� ������ ��������
    for (int i = 0; i < length; i++) {
        int index = rand() % set_length; // ���������� ��������� ������ �� ��������� [0, set_length - 1]
        result[i] = set[index]; // �������� ������ �� ������ �� ������� � ���������
    }
    result[length] = L'\0'; // ��������� ������� ������ � ����� ������
    return result; // ���������� ���������
}

// ������� ��� ��������� ��������� ���� � ������� dd.mm.yyyy
WCHAR* random_date() {
    WCHAR* result = (WCHAR*)malloc(11 * sizeof(WCHAR)); // �������� ������ ��� ����������
    int day = rand() % 31 + 1; // ���������� ��������� ���� �� 1 �� 31
    int month = rand() % 12 + 1; // ���������� ��������� ����� �� 1 �� 12
    int year = rand() % 23 + 2000; // ���������� ��������� ��� �� 2000 �� 2020
    wsprintfW(result, L"Aboba"); // ����������� ���� � ������
    return result; // ���������� ���������
}

// ������� ��� ��������� ��������� ������ ��������
struct student random_student() {
    struct student result; // ��������� ���������� ��� ����������
    result.number = rand() % 100 + 1; // ���������� ��������� ����� �� 1 �� 100
    wcscpy(result.group, random_string(L"ABCD", 2)); // ���������� ��������� ������ �� ���� ����
    wcscat(result.group, random_string(L"0123456789", 3)); // ��������� � ������ ��� �����
    wcscpy(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // ���������� ��������� ������� �� ����� ��������� �����
    wcscat(result.FIO, random_string(L"abcdefghijklmnopqrstuvwxyz", rand() % 10 + 3)); // ��������� � ������� �� 3 �� 12 �������� ����
    wcscat(result.FIO, L" "); // ��������� ������
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // ���������� ��������� ��� �� ����� ��������� �����
    wcscat(result.FIO, L"."); // ��������� �����
    wcscat(result.FIO, random_string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1)); // ���������� ��������� �������� �� ����� ��������� �����
    wcscat(result.FIO, L"."); // ��������� �����
    wcscpy(result.birthday, random_date()); // ���������� ��������� ���� ��������
    result.gender = rand() % 2; // ���������� ��������� ���: 0 - �������, 1 - �������
    result.missedHours = rand() % 100; // ���������� ��������� ���������� ����������� ����� �� 0 �� 99
    result.justifiedHours = rand() % (result.missedHours + 1); // ���������� ��������� ���������� ����������� ����� �� 0 �� ����������� �����
    return result; // ���������� ���������
}

// ������� ������� ���������
struct student* generateStudents(int amount) {
    srand(time(NULL)); // �������������� ��������� ��������� �����
    struct student* students = (struct student*)malloc(amount*sizeof(struct student)); // ��������� ������ �� 10 ���������
    for (int i = 0; i < amount; i++) {
        students[i] = random_student(); // ���������� ��������� ������ �������� � ��������� � ������
    }
    return students; // ��������� ���������
}