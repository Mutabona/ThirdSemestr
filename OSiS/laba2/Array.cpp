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

    

public:
    Array(int _size): size(_size) {
        array = new int[size];
    }

    void sort() {
        qsort(0, size-1);
    }

    void fill() {
        srand(time(NULL));
        for(int i = 0; i < size; i++) {
            array[i] = rand()%10000;
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

    ~Array() {
        delete[] array;
    }
};