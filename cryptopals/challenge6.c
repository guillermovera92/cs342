#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

#define BITS_IN_BYTE 8
#define KEYSIZE_MIN 2
#define KEYSIZE_MAX 40

// Compile with: gcc challenge6.c crypto-utils.c -g -o challenge6

static char *sInputStr1 = "this is a test";
static char *sInputStr2 = "wokka wokka!!!";
static int trueHammingDistance = 37;

int getHammingDistance(char *str1, char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return -1;
    }

    char *xored = xorBuffers(str1, str2, strlen(str1), strlen(str2));
    char MASK = 0x01;
    int count = 0;
    for (int i = 0; i < strlen(str1); i++) {
        char currentByte = xored[i];
        for (int j = 0; j < BITS_IN_BYTE; j++) {
            if (currentByte & MASK == 1) {
                count++;
            }
            currentByte >>= 1;
        }   
    }

    return count;
}

int main(int argc, char *argv[]) {

    int hamming = getHammingDistance(sInputStr1, sInputStr2);

    if (hamming == trueHammingDistance) {
        printf("Hamming distance success\n");
    } else {
        printf("Failed Hamming distance %d\n", hamming);
    }

    for (int i = KEYSIZE_MIN; i < KEYSIZE_MAX; i++) {
        /* code */
    }

    return 0;
}