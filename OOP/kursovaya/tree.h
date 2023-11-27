#ifndef TREE
#define TREE

#include <stdio.h>
#include <windows.h>

#include "student.h"

struct node {
    struct student student;
    struct node* left;
    struct node* right;
};

void addStudent();
struct node* addNode(struct node* node, struct student student);
void getStudents(struct node* node, struct student* students, int* i);

#endif