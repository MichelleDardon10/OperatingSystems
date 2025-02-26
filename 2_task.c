#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Create a new process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else {
        // Parent process
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);  // Wait for the specific child process

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("Parent Process: Child has finished execution.\n");
        }
    }

    return 0;
}