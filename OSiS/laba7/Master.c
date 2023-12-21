#include <unistd.h>
#include <stdio.h>

#define M 3

int main(int argc, char *argv[], char *envp[]) {
    __pid_t this = getpid();
    __pid_t parent = getppid();

    printf("This id: %d, Parent id: %d\n", this, parent);

    for (int i = 0; i < M; i++) {
        char number[3];
        sprintf(number, "%d", i);
        int pid = fork();
        if (pid == -1) {
            printf("Oh hell no");
        } else if (pid == 0) {
            execle("Sort", "Sort", number, NULL, envp);
        }     
    }

    sleep(2);
}