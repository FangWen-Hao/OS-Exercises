/*
Example:

`./Q8-25 19986`
```
The address 19986 contains:
page number = 4
offset = 3602
```
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *ptr;

    unsigned long givenAddress;
    unsigned long virtualAddress;
    unsigned long pageNumber;
    unsigned long pageOffset;

    if (argc != 2) {
        printf("Incomplete arguments! \n Usage example: ./a.out 19986. Values beyond 32-bits will be truncated to 32-bits.\n");
        return 1;
    }

    if (argc > 2) {
        printf("Too many arguments! \n Usage example: ./a.out 19986. Values beyond 32-bits will be truncated to 32-bits.\n");
        return 1;
    }

    givenAddress = strtoul(argv[1], &ptr, 10);

    virtualAddress = givenAddress & 0x0FFFFFFFF;

    pageNumber = virtualAddress >> 12;
    pageOffset = virtualAddress & 0x0FFF;
    // 4 KB page = 2^12 bytes // 12 bits for page offset // 32 - 12 = 20 bits page number.
     // (int)strtol(str, (char **)NULL, 10);

    printf("The address %lu contains:\n", virtualAddress);
    printf("page number = %lu\n", pageNumber);
    printf("pageOffset = %lu\n", pageOffset);

    return 0;
}
