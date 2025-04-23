#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5]; // 5 semaphores for chopsticks

void *philos(void *num);
void eat(int ph);

int main() {
    int i;
    int n[5];                  // Philosopher numbers
    pthread_t T[5];            // Thread IDs

    // Initialize all chopstick semaphores to 1 (available)
    for (i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Create threads for each philosopher
    for (i = 0; i < 5; i++) {
        n[i] = i;
        pthread_create(&T[i], NULL, philos, (void *)&n[i]);
    }

    // Wait for all philosopher threads to finish
    for (i = 0; i < 5; i++) {
        pthread_join(T[i], NULL);
    }

    return 0;
}
void *philos(void *num) {
    int ph = *(int *)num;

    printf("Philosopher %d wants to eat\n", ph);

    // To avoid deadlock, let the last philosopher pick right first
    if (ph == 4) {
        printf("Philosopher %d tries to pick the RIGHT chopstick\n", ph);
        sem_wait(&chopstick[(ph + 1) % 5]);  // Right chopstick

        printf("Philosopher %d picked the RIGHT chopstick\n", ph);
        printf("Philosopher %d tries to pick the LEFT chopstick\n", ph);
        sem_wait(&chopstick[ph]);            // Left chopstick
        printf("Philosopher %d picked the LEFT chopstick\n", ph);
    } else {
        printf("Philosopher %d tries to pick the LEFT chopstick\n", ph);
        sem_wait(&chopstick[ph]);            // Left chopstick

        printf("Philosopher %d picked the LEFT chopstick\n", ph);
        printf("Philosopher %d tries to pick the RIGHT chopstick\n", ph);
        sem_wait(&chopstick[(ph + 1) % 5]);  // Right chopstick
        printf("Philosopher %d picked the RIGHT chopstick\n", ph);
    }

    eat(ph);
    sleep(2);  // Simulate eating time

    printf("Philosopher %d has finished eating\n", ph);

    // Release both chopsticks
    sem_post(&chopstick[ph]);                // Left chopstick
    printf("Philosopher %d released the LEFT chopstick\n", ph);

    sem_post(&chopstick[(ph + 1) % 5]);      // Right chopstick
    printf("Philosopher %d released the RIGHT chopstick\n", ph);

    pthread_exit(NULL);
}
void eat(int ph) {
    printf("Philosopher %d is eating...\n", ph);
}
