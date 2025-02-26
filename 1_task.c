#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  // Include for wait()

int main() {
    // Create a new process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(1);  // Sleep to observe execution order
        printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent Process: PID=%d\n", getpid());
        wait(NULL);  // Wait for the child process to finish
    }

    return 0;
}