#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define SIZE 0x1000

void* core_function(void* arg) {
    int core_id = *(int*)arg;
    char* buffer = malloc(SIZE);

    if (!buffer) {
        perror("malloc");
        return NULL;
    }

    if (core_id == 0) {
        // Core 0 - Sequential Access
        for (int i = 0; i < SIZE; i++) buffer[i] = i % 256;
        printf("Core 0 done with sequential write\n");
    } else {
        // Core 1 - Random Access
        for (int i = 0; i < 1000; i++) buffer[rand() % SIZE] ^= 0xAA;
        printf("Core 1 done with random write\n");
    }

    free(buffer);
    return NULL;
}

int main() {
    pthread_t core_threads[3];
    int core_ids[3] = {0, 1, 2};
    //int core_ids[2] = {0, 1};

    for (int i = 0; i < 3; ++i)
        pthread_create(&core_threads[i], NULL, core_function, &core_ids[i]);

    for (int i = 0; i < 3; ++i)
        pthread_join(core_threads[i], NULL);

    return 0;
}

