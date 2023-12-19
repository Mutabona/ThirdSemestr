#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 64

int main(int argc, char *argv[]) {
    int number = 0;

    if (argv[1]) number = atoi(argv[1]);

    __pid_t this = getpid();
    __pid_t parent = getppid();

    printf("\nNumber: %d, This id: %d, Parent id: %d\n", number, this, parent);

    int array[size];

    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        array[i] = rand()%100;
    }

    int i, key, j;
    for (i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] < key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }

    for(int i = 0; i < size; i++) {
        printf("N%d: %d ", number, array[i]);
    }
    printf("\n");
}