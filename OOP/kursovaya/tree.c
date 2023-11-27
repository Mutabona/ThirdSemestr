#include "tree.h"

struct node* addNode(struct node* node, struct student student) {
    if(!node) {
        node = (struct node*)malloc(sizeof(struct node));
        node->student = student;
    }
    else if (student.number < node->student.number) {
        node->left = addNode(node->left, student);
    }
    else {
        node->right = addNode(node->right, student);
    }
    return node;
}

int getStudents(struct node* node, struct student* students, int i) {
    if (!node) return i;
    i = getStudents(node->left, students, i);
    students[i++] = node->student;
    //wprintf(L"student %d\n", students[i-1].number);
    i = getStudents(node->right, students, i);
    return i;
}