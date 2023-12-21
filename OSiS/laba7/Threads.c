#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define size 64

int array[size];

void* sort(void* arg) {
    pthread_t thid = pthread_self();
    printf("Sort:pthreadId = %ld\n", thid);

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
    pthread_exit(0);
}

void* print(void* arg) {
    pthread_t *sortThreadId = (pthread_t*)arg;
    pthread_join(*sortThreadId, (void **)NULL);
    pthread_t thid = pthread_self();
    printf("Print:pthreadId = %ld\n", thid);

    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    pthread_exit(0);
}

int main() {
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        array[i] = rand()%100;
    }

    pthread_t sortThreadId, printThreadId;
    int sortResult, printResult;

    printResult = pthread_create(&printThreadId, (pthread_attr_t*)NULL, print, &sortThreadId);
    sortResult = pthread_create(&sortThreadId, (pthread_attr_t*)NULL, sort, NULL);
    
    printf("Print:pthreadId = %ld, Sort:pthreadId = %ld\n", sortThreadId, printThreadId);

    pthread_join(printThreadId, (void **)NULL);
}