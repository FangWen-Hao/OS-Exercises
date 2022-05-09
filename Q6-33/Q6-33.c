#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "args_struct.h"


double g_PI = 0;
pthread_mutex_t lock;

void* monteCarlo(void* v_as) {
    pthread_mutex_lock(&lock);
    args_struct* as = v_as;
    int arr_length     = (*as).arr_length;
    for (int i = 0; i < arr_length; i++) {
        double random_x = rand()/(double)RAND_MAX;
        double random_y = rand()/(double)RAND_MAX;
        g_PI += random_x*random_x + random_y*random_y <= 1;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    // clock_t timeBfore = clock();

    args_struct* args = malloc(sizeof(args_struct));
    void* v_args;
    double resultPi = 0;

    int numberOfThreads = 16;
    pthread_t tid[numberOfThreads];

    if (argc != 2) {
        printf("No arguments given, please try again.\n");
        exit(1);
    }

    int numberOfPoints = atoi(argv[1]);
    (*args).arr_length = (numberOfPoints / numberOfThreads);
    v_args = (void*)(args);
    srand(time(NULL));

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("The mutex has failed to initialized, program aborted.\n");
        exit(1);
    }

    for (int i = 0; i < numberOfThreads; i++) {
        if (pthread_create(&(tid[i]), NULL, &monteCarlo, v_args) != 0) {
            printf("The Monte Carlo thread was created incorrectly, program aborted.\n");
            exit(0);
        }
    }

    for (int i = 0; i < numberOfThreads; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    resultPi = g_PI*4.0/numberOfPoints;
    printf("The value of Pi is: %f\n", resultPi);

    // clock_t timeTaken = (double)(clock() - timeBfore) / CLOCKS_PER_SEC;
    // printf("Total time taken by CPU: %ld seconds.\n", timeTaken);
    return 0;
}
