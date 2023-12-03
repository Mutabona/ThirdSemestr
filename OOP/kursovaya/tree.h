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
int getStudentsListByFIO(struct node* node, struct student* students, int i, WCHAR FIO[30]);
size_t height(struct node* node);
int balanceFactor(struct node* p);
void fixHeight(struct node* node);
struct node* rotateRight(struct node* p);
struct node* rotateLeft(struct node* q);
struct node* balance(struct node* p);
struct node* findMin(struct node* node);
struct node* removeMin(struct node* node);
struct node* removeNode(struct node* p, int k);

#endif