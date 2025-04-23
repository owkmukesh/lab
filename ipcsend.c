#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512  // Maximum message length

// Message structure
struct my_msg {
    long int msg_type;
    char some_text[MAX_TEXT];
};

int main() {
    int running = 1;
    int msgid;
    struct my_msg some_data;
    char buffer[50];  // Temporary buffer for user input

    // Create message queue
    msgid = msgget((key_t)14534, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Failed to create message queue");
        exit(EXIT_FAILURE);
    }

    while (running) {
        printf("Enter some text: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            perror("Error reading input");
            continue;
        }

        // Remove trailing newline if any
        buffer[strcspn(buffer, "\n")] = '\0';

        some_data.msg_type = 1;
        strncpy(some_data.some_text, buffer, MAX_TEXT - 1);
        some_data.some_text[MAX_TEXT - 1] = '\0'; // Ensure null termination

        // Send message
        if (msgsnd(msgid, (void *)&some_data, strlen(some_data.some_text) + 1, 0) == -1) {
            perror("Message send failed");
        }

        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }

    return 0;
}
