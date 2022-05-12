#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int number = 0;
pthread_mutex_t mutex;

struct ThreadData {
    int id;
    int threadCount;
};

void* threadFunc(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    printf("Hello! My id: %d, all: %d \n", data->id, data->threadCount);
    return NULL;
}

int main() {
    unsigned threadCount = 0;
    printf("Please, enter threads count:\n");
    if (scanf("%u", &threadCount) == 0 && threadCount == 0) {
        printf ("Input error\n");
        return 0;
    }
    
    pthread_t threads[threadCount];
    struct ThreadData threadData[threadCount];

    /* init threads  */
    for(int i = 0; i < threadCount; ++i) {
        threadData[i].id = i;
        threadData[i].threadCount = threadCount;
        
        if((pthread_create(&threads[i], NULL, threadFunc, &threadData[i]))) {
            fprintf(stderr, "error: pthread_create\n");
            exit (EXIT_FAILURE);
        }
    }

    /* block until all threads complete */
    for(int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}