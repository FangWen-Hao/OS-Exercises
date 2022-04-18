#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

u_int32_t buffer[BUFFER_SIZE];

void *getFibonacciNumber(void *param) {
    int *p = param;
    int numberOfFibonacciNumbers = *p;

    buffer[0] = 0;
    buffer[1] = 1;
    for (int i = 2; i < numberOfFibonacciNumbers; i++)
    {
        buffer[i] = buffer[i - 1] + buffer[i - 2];
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid;
    pthread_attr_t attr;
    if (argc < 2) {
        printf("No arguments given, program aborted.\n");
        exit(1);
    }

    else if (argc > 2) {
        printf("Too many arguments given, program aborted. \n");
        exit(1);
    }

    int numberOfFibonacciNumbers = atoi(argv[1]);

    if (numberOfFibonacciNumbers >= 48)
    {
        printf("The desired amounts of numbers, %d, will overflow, however the overflowed result will still be shown.\n", numberOfFibonacciNumbers);
    }
    // get thread attributes
    pthread_attr_init(&attr);

    // create a thread
    pthread_create(&tid, &attr, getFibonacciNumber, &numberOfFibonacciNumbers);

    // wait for each thread to finish
    pthread_join(tid, NULL);

    for (int i = 0; i < numberOfFibonacciNumbers; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}
