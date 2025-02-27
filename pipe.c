#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid;
    char write_msg[] = "Hello from Parent";
    char read_msg[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid > 0) { // Parent process
        close(fd[0]); // Close reading end
        printf("Parent Process: Writing \"%s\"\n", write_msg);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // Close writing end
    } else { // Child process
        close(fd[1]); // Close writing end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child Process: Received \"%s\"\n", read_msg);
        close(fd[0]); // Close reading end
    }

    return 0;
}