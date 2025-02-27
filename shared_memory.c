#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key = 1234;  // Unique shared memory key
    int shmid;
    char *shared_memory;

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory to parent process
    shared_memory = (char *) shmat(shmid, NULL, 0);
    if (shared_memory == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Write to shared memory
    char message[] = "Shared Memory Example";
    printf("Parent Process: Writing \"%s\"\n", message);
    strcpy(shared_memory, message);

    // Fork child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        sleep(1); // Ensure parent writes first

        // Attach shared memory to child
        char *child_memory = (char *) shmat(shmid, NULL, 0);
        if (child_memory == (char *) -1) {
            perror("shmat failed");
            exit(1);
        }

        // Read from shared memory
        printf("Child Process: Read \"%s\"\n", child_memory);

        // Detach shared memory
        shmdt(child_memory);

        exit(0);
    }

    // Parent waits for child
    wait(NULL);

    // Detach and remove shared memory
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}