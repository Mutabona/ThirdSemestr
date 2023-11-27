#include "tree.h"

void addStudent() {
    printf("Какиш");
    return;
}

struct node* addNode(struct node* node, struct student student) {
    if(!node) {
        node = (struct node*)malloc(sizeof(node));
        node->student = student;
        return node;
    }
    if (student.number < node->student.number) {
        node->left = addNode(node->left, student);
    }
    else {
        node->right = addNode(node->right, student);
    }
    return node;
}

void getStudents(struct node* node, struct student* students, int* i) {
    if (!node) return;
    getStudents(node->left, students, i);
    students[(*i)++] = node->student;
    getStudents(node->right, students, i);
}