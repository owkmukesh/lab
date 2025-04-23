#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buffer[100];
    pid_t p;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    p = fork();

    if (p > 0) {
        // Parent process
        close(fd[0]); // Close reading end
        printf("Parent passing value to child\n");
        write(fd[1], "hello", 6); // Write to pipe
        close(fd[1]); // Close writing end
        wait(NULL); // Wait for child process
    } else if (p == 0) {
        // Child process
        close(fd[1]); // Close writing end
        int n = read(fd[0], buffer, sizeof(buffer));
        buffer[n] = '\0'; // Null-terminate the string
        printf("%s", buffer);
        close(fd[0]); // Close reading end
    } else {
        // Fork failed
        perror("Fork failed");
        return 1;
    }

    return 0;
}
