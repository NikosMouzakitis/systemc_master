#include <stdlib.h>
#include <stdio.h>

int main() {
    int size = 0x1000;
    char *buffer = malloc(size);
    
    // Pattern 1: Sequential access (good for baseline)
    for (int i = 0; i < size; i++) buffer[i] = i % 256;
    
    // Pattern 2: Random access (stress NoC)
//    for (int i = 0; i < 1000; i++) 
//        buffer[rand() % size] ^= 0xAA;
    
    free(buffer);
    return 0;
}
