#include "tree.h"

struct node* addNode(struct node* node, struct student student) {
    if(!node) {
        node = (struct node*)malloc(sizeof(struct node));
        node->student = student;
        node->height = 1;
    }
    else if (student.number < node->student.number) {
        node->left = addNode(node->left, student);
    }
    else {
        node->right = addNode(node->right, student);
    }
    return balance(node);
}

int getStudents(struct node* node, struct student* students, int i) {
    if (!node) return i;
    i = getStudents(node->left, students, i);
    students[i++] = node->student;
    i = getStudents(node->right, students, i);
    return i;
}

int getStudentsListByFIO(struct node* node, struct student* students, int i, WCHAR FIO[30]) {
    if (!node) return i;
    i = getStudentsListByFIO(node->left, students, i, FIO);
    if (!wcscmp(node->student.FIO, FIO)) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByFIO(node->right, students, i, FIO);
    return i;
}

size_t height(struct node* node) {
	return node?node->height:0;
}

int balanceFactor(struct node* p) {
	return height(p->right)-height(p->left);
}

void fixHeight(struct node* node) {
	unsigned char hl = height(node->left);
	unsigned char hr = height(node->right);
	node->height = (hl>hr?hl:hr)+1;
}

struct node* rotateRight(struct node* p) {
	struct node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

struct node* rotateLeft(struct node* q) {
	struct node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

struct node* balance(struct node* p) {
	fixHeight(p);
	if( balanceFactor(p)==2 ) {
		if( balanceFactor(p->right) < 0 )
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if( balanceFactor(p)==-2 ) {
		if( balanceFactor(p->left) > 0  )
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}

struct node* findMin(struct node* node) {
	return node->left?findMin(node->left):node;
}

struct node* removeMin(struct node* node) {
	if(!node->left)
		return node->right;
	node->left = removeMin(node->left);
	return balance(node);
}

struct node* removeNode(struct node* p, int k) {
	if( !p ) return NULL;
	if( k < p->student.number )
		p->left = removeNode(p->left,k);
	else if( k > p->student.number )
		p->right = removeNode(p->right,k);
    else //  k == p->key 
	{
		struct node* q = p->left;
		struct node* r = p->right;
		free(p);
		if( !r ) return q;
		struct node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
    return balance(p);
}