#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int philosopher_ids[NUM_PHILOSOPHERS];

void think(int id) {
    printf("Philosopher %d is thinking...\n", id);
    sleep(rand() % 3 + 1);  // Thinking for a random time between 1 and 3 seconds
}

void eat(int id) {
    printf("Philosopher %d is eating...\n", id);
    sleep(rand() % 3 + 1);  // Eating for a random time between 1 and 3 seconds
}

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        think(id);

        // Pick up forks
        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;

        if (id % 2 == 0) {
            // Pick up left fork first for even numbered philosophers
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            // Pick up right fork first for odd numbered philosophers
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        eat(id);

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
    }
}

int main() {
    srand(time(NULL));

    // Initialize the mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create the philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join the philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
