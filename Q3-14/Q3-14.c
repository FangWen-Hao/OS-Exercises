#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "collatzConjecture.h"

int main(int argc, char *argv[]) {
    int inputNumber;
    pid_t pid;

    if ((argc > 1) && (atoi(argv[1]) != 0)) {
      // If the user has put arguments with the command and the argument is a number,
      // then put the number in the local variable
        sscanf(argv[1], "%d", &inputNumber);
        if (inputNumber < 1) {
          // If the input number is not a positive  integer, notify the user of an error
            printf("Error: input is not a positive integer! %d\n", inputNumber);
            return 1;
        }
    }
    else {
      // Error handling
      if (argc <= 1) {
        // If the user didnt input any aditional arguments, notify them.
        printf("Error: program has been called without any arguments in the command line.\n");
        return 1;
      }
        else if (atoi(argv[1]) == 0) {
          // If the input is not a numeric one, notify the user.
          printf("Error: input is not a valid char.\n");
          return 1;
        }
        else {
          // If there is another error that hasn't been accounted for, notify them.
          // Default clause: this shouldn't be triggered but in case of it is here.
          printf("Error");
          return 1;
        }
    }

    pid = fork();

    if (pid == 0) {
        while (1) {
            if (inputNumber == 1) {
              // If the number is 1, then break and return
                printf("%d\n", inputNumber);
                break;
            }
            else {
              // If the number isn't 1, then print it as a list of numbers, demarked by ","
                printf("%d, ", inputNumber);
            }
            // While the number isn't 1, rinse and repeat the Collatz conjecture.
            inputNumber = collatzConjecture(inputNumber);
        }
    }
    else if (pid > 0) {
      // If the child process is done, notify the user of such and stop waiting.
        wait(NULL);
        printf("Child process completed!\n");
    }
    return 0;
}
