#include "tree.h"

struct node* addNode(struct node* node, struct student student) {
    if(!node) {
        node = (struct node*)malloc(sizeof(struct node));
        node->student = student;
        node->height = 1;
        node->right = NULL;
        node->left = NULL;
        return node;
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

int height(struct node* node) {
	return node?node->height:0;
}

int balanceFactor(struct node* p) {
	return height(p->right)-height(p->left);
}

void fixHeight(struct node* node) {
	int hl = height(node->left);
	int hr = height(node->right);
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

struct node* removeNode(struct node* p, int number) {
	if( !p ) return NULL;
	if( number < p->student.number )
		p->left = removeNode(p->left, number);
	else if( number > p->student.number )
		p->right = removeNode(p->right, number);
    else
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

struct student* _getStudentByNumber(struct node* node, int number) {
    if (!node) return NULL;
    if (node->student.number < number) {
        return _getStudentByNumber(node->right, number);
    } else if (node->student.number > number) {
        return _getStudentByNumber(node->left, number);
    } else {
        return &node->student;
    }   
}

int getStudentsListByGroup(struct node* node, struct student* students, int i, WCHAR group[6]) {
    if (!node) return i;
    i = getStudentsListByGroup(node->left, students, i, group);
    if (!wcscmp(node->student.group, group)) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByGroup(node->right, students, i, group);
    return i;
}

int getStudentsListByBirthday(struct node* node, struct student* students, int i, WCHAR birthday[11]) {
    if (!node) return i;
    i = getStudentsListByBirthday(node->left, students, i, birthday);
    if (!wcscmp(node->student.birthday, birthday)) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByBirthday(node->right, students, i, birthday);
    return i;
}

int getStudentsListByGender(struct node* node, struct student* students, int i, int gender) {
    if (!node) return i;
    i = getStudentsListByGender(node->left, students, i, gender);
    if (node->student.gender == gender) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByGender(node->right, students, i, gender);
    return i;
}

int getStudentsListByJustifiedHours(struct node* node, struct student* students, int i, int justifiedHours) {
    if (!node) return i;
    i = getStudentsListByJustifiedHours(node->left, students, i, justifiedHours);
    if (node->student.justifiedHours == justifiedHours) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByJustifiedHours(node->right, students, i, justifiedHours);
    return i;
}

int getStudentsListByMissedHours(struct node* node, struct student* students, int i, int missedHours) {
    if (!node) return i;
    i = getStudentsListByMissedHours(node->left, students, i, missedHours);
    if (node->student.missedHours == missedHours) {
        students = (struct student*)realloc(students, sizeof(struct student)*(i+1));
        students[i++] = node->student;
    }
    i = getStudentsListByMissedHours(node->right, students, i, missedHours);
    return i;
}

int getStudentsListWithUnjustifiedHours(struct node* node, struct student* students, int i) {
    if (!node) return i;
    i = getStudentsListWithUnjustifiedHours(node->left, students, i);
    if (node->student.missedHours > node->student.justifiedHours) {
        students = (struct student*)realloc(students, (i+1) * sizeof(struct student));
        students[i++] = node->student;
    }
    i = getStudentsListWithUnjustifiedHours(node->right, students, i);
    return i;
}

void saveToFile(struct node* node, FILE* file) {
    if (!node) return;
    fwrite(node, sizeof(struct node), 1, file);
    saveToFile(node->left, file);
    saveToFile(node->right, file);
}

struct node* loadFromFile(struct node* node, FILE* file, int *i) {
    if (!feof(file)) {
        node = (struct node*)malloc(sizeof(struct node));
        fread(node, sizeof(struct node), 1, file);
        if (node->left)
            node->left = loadFromFile(node->left, file, i);
        node->student.number = *i;
        (*i)++;
        if (node->right)
            node->right = loadFromFile(node->right, file, i);       
    }
    else {
        return NULL;
    }
    return node;
}

void freeTree(struct node* node) {
    if(!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int getJustifiedHours(struct node* node) {
    if (!node) return 0;
    return getJustifiedHours(node->left) + getJustifiedHours(node->right) + node->student.justifiedHours;
}

int getMissedHours(struct node* node) {
    if (!node) return 0;
    return getMissedHours(node->left) + getMissedHours(node->right) + node->student.missedHours;
}