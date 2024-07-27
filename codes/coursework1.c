#include <stdio.h>
#include <stdlib.h>
void printBytes(void *ptr, int numBytes) {
    int i;
    int *ptrInt = (int *) ptr;
    printf("Starting at memory address %p:\n", ptrInt);
    for (i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, *(ptrInt + i));
    }
}
int main() {
    int data[] = {2, 3, 5, 7, 11};
    int *ptr = data;
    printBytes(ptr, 5);
    return 0;
}
/*
Execution
gcc -ansi -c coursework1.c -o coursework1.o
gcc coursework1.o -o coursework1
./coursework1
*/