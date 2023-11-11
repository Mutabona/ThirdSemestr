#include<iostream>
#include<time.h>

class Array {
private:
    int* array;
    int size;

    void qsort(int start, int end) {
        if (start > end) return;

        int i = start;
        int j = start;

        int pivot = array[end];

        while (i <= end) {
            if (array[i] > pivot) {
                i++;
            }
            else {
                swap(i, j);
                i++;
                j++;
            }
        }

        int pos = j-1;

        qsort(start, pos-1);
        qsort(pos+1, end);
    }

    void bubleSort() {
        for (int i = 0; i < size-1; i++) {
            for (int j = i; j < size; j++) {
                if (array[j] < array[j+1]) {
                    int temp = array[j+1];
                    array[j+1] = array[j];
                    array[j] = temp; 
                }
            }
        }
    }
    

public:
    Array(int _size): size(_size) {
        array = new int[size];
        fill();
    }

    void sort() {
        qsort(0, size-1);
    }

    void fill() {
        srand(time(NULL));
        for(int i = 0; i < size; i++) {
            array[i] = rand()%100;
        }
    }

    void swap(int pos1, int pos2) {
        int temp = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = temp;
    }

    void printArray() {
        for (int i = 0; i < size; i++)
            printf("%d ", array[i]);
        printf("\n");
    }

    void printArray(int i) {
        for (int j = 0; j < size; j++) {
            printf("N%d: %d\n", i, array[j]);
        }
    }

    int& operator[](const int i) {
        return array[i];
    }

    ~Array() {
        delete[] array;
    }
};