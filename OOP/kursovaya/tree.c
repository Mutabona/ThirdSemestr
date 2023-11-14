#include <stdio.h>
#include <tchar.h>

#include "student.c"


struct Node {
    struct student student;
    struct Node* left;
    struct Node* right;
};

void addStudent() {
    wprintf(L"Есть контакт");
    return;
}