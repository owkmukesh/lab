#include <stdio.h>

// Function to clear invalid input
void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    int buffer[10];
    int bufsize = 10;
    int in = 0, out = 0, count = 0;
    int produce, consume, choice = 0;

    while (1) {
        printf("\n\n1. Produce\n2. Consume\n3. Exit");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: // Produce
                if (count == bufsize) {
                    printf("Buffer is Full.");
                } else {
                    printf("Enter the value to produce: ");
                    if (scanf("%d", &produce) != 1) {
                        printf("Invalid value! Try again.");
                        clearInputBuffer();
                        break;
                    }
                    buffer[in] = produce;
                    in = (in + 1) % bufsize;
                    count++;
                    printf("Produced: %d", produce);
                }
                break;

            case 2: // Consume
                if (count == 0) {
                    printf("Buffer is Empty.");
                } else {
                    consume = buffer[out];
                    out = (out + 1) % bufsize;
                    count--;
                    printf("Consumed: %d", consume);
                }
                break;

            case 3: // Exit
                printf("Exiting program...");
                return 0;

            default:
                printf("Invalid choice. Please try again.");
                break;
        }
    }
}
