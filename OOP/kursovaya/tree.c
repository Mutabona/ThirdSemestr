#include <stdio.h>
#include <student.c>


struct Node {
    struct student student;
    struct Node* left;
    struct Node* right;
};

struct Node* addStudent(struct Node* node) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->student = getStudent();
    newNode->left=NULL;
    newNode->right=NULL;
    node = addNode(node, newNode);
    return node;
}

struct Node* addNode(struct Node* node, struct Node* newNode) {
    if (!node)
        node = newNode;
    else if (node->student.number > newNode->student.number)
        node->left = addNode(node->left, newNode);
    else
        node->right = addNode(node->right, newNode);
    return node;
}

struct Node* deleteNode(struct Node* node, int number) {
    if (!node)
        return NULL;
    if (node->student.number == number) {
        struct Node* left = node->left;
        left = addNode(left, node->right);
        free(node);
        return left;   
    }
    else if (node->student.number < number)
        node->right = deleteNode(node->right, number);
    else
        node->left = deleteNode(node->left, number);
    return node;
}