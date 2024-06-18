#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 2
#define ITEM_COUNT 5 // Total number of items to produce/consume

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int produced_count = 0, consumed_count = 0;

sem_t empty; // Semaphore to count empty slots in the buffer
sem_t full;  // Semaphore to count full slots in the buffer
pthread_mutex_t mutex; // Mutex to protect the critical section

void *producer(void *arg) {
    int item;
    while (1) {
        if (produced_count >= ITEM_COUNT) break; // Stop after producing ITEM_COUNT items

        item = rand() % 100; // Produce an item
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        if (produced_count < ITEM_COUNT) {
            buffer[in] = item;
            printf("Producer produced: %d\n", item);
            in = (in + 1) % BUFFER_SIZE;
            produced_count++;
        }

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increment the count of full slots

        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while (1) {
        if (consumed_count >= ITEM_COUNT) break; // Stop after consuming ITEM_COUNT items

        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        if (consumed_count < ITEM_COUNT) {
            item = buffer[out];
            printf("Consumer consumed: %d\n", item);
            out = (out + 1) % BUFFER_SIZE;
            consumed_count++;
        }

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increment the count of empty slots

        sleep(1); // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    // Join the threads (wait for their completion)
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Production and consumption completed.\n");

    return 0;
}
