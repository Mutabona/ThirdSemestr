#ifndef TREE
#define TREE

#include <stdio.h>
#include <windows.h>

#include "student.h"

struct node {
    struct student student;
    size_t height;
    struct node* left;
    struct node* right;
};

struct node* addNode(struct node* node, struct student student);
int getStudents(struct node* node, struct student* students, int i);
size_t height(struct node* node);
int balanceFactor(struct node* p);
void fixHeight(struct node* node);
struct node* rotateRight(struct node* p);
struct node* rotateLeft(struct node* q);
struct node* balance(struct node* p);
struct node* findMin(struct node* node);
struct node* removeMin(struct node* node);
struct node* removeNode(struct node* p, int number);
struct student* _getStudentByNumber(struct node* node, int number);
int getStudentsListByFIO(struct node* node, struct student* students, int i, WCHAR FIO[30]);
int getStudentsListByGroup(struct node* node, struct student* students, int i, WCHAR group[6]);
int getStudentsListByGender(struct node* node, struct student* students, int i, int gender);
int getStudentsListByBirthday(struct node* node, struct student* students, int i, WCHAR birthday[11]);
int getStudentsListByJustifiedHours(struct node* node, struct student* students, int i, int justifiedHours);
int getStudentsListByMissedHours(struct node* node, struct student* students, int i, int missedHours);
void saveToFile(struct node* node, FILE* file);
struct node* loadFromFile(struct node* node, FILE* file, int *i);

#endif