#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
    pid_t pid;
    int i;

    printf("Parent Process: PID=%d\n", getpid());

    // Loop to create multiple child processes
    for (i = 1; i <= NUM_CHILDREN; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) { // Child process
            printf("Child %d: PID=%d, Parent PID=%d\n", i, getpid(), getppid());
            exit(0); // Child exits after printing
        }
    }

    // Parent waits for all child processes to finish
    for (i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    return 0;
}