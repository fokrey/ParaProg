#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

struct ThreadData {
    int leftBorder;
    int rightBorder;
    double result;
};

void* threadFunc(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    double localSum = 0;
    for(int i = data->leftBorder; i < data->rightBorder; ++i) {
        localSum += 1.0 / i;
    }
    //printf ("Partial sum is %f\n", localSum); 
    data->result = localSum;
    return NULL;
}

int main(int argc, char* argv[]) {
    unsigned threadCount = 0, N = 0;

    printf ("Please, enter threads counts and number N\n");
    if ((scanf("%u %u", &threadCount, &N)) != 2 && threadCount == 0 && N == 0) {
        printf ("Input error\n");
        return 0;        
    }

    pthread_t* threads = (pthread_t*)malloc(threadCount * sizeof(pthread_t));
    struct ThreadData* threadData = (struct ThreadData*)malloc(threadCount * sizeof(struct ThreadData));

    /* init threads  */
    for(int i = 0; i < threadCount; ++i) {
        threadData[i].leftBorder  = N * i / threadCount + 1;
        threadData[i].rightBorder = N * (i + 1) / threadCount + 1;
        if(threadData[i].rightBorder > N) {
            threadData[i].rightBorder = N + 1; 
        }        

        if((pthread_create(&threads[i], NULL, threadFunc, &threadData[i]))) {
            fprintf(stderr, "error: pthread_create\n");
            return EXIT_FAILURE;
        }
    }

    double ans = 0;
    /* block until all threads complete */
    for(int i = 0; i< threadCount; ++i) {
        pthread_join(threads[i], NULL);
        ans += threadData[i].result;
    }

    printf("ans = %f\n", ans);

    free(threads);
    free(threadData);
}