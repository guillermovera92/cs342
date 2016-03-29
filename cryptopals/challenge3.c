#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

#define MAX_ASCII 128

// Compile with: gcc challenge3.c crypto-utils.c -g -o challenge3

static char *sInputStr = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

int main(int argc, char *argv[]) {

    int bytesLen = 0;
    char *inputBuffer = hexStrToBytes(sInputStr, &bytesLen);

    char *tempBuffer = malloc(bytesLen);
    char *outputBuffer = malloc(bytesLen);

    int maxScore = 0;
    int currentScore = 0;
    char bestGuessKey;

    for (unsigned int i = 0; i < MAX_ASCII; i++) {
        memset(tempBuffer, i, bytesLen);
        char *bytesXored = xorBuffers(inputBuffer, tempBuffer, bytesLen, bytesLen);
        currentScore = scoreStr(bytesXored, bytesLen);
        if (currentScore > maxScore) {
            maxScore = currentScore;
            bestGuessKey = i;
            outputBuffer = bytesXored;
        }
    }

    printf("Best guess key: %c\n", bestGuessKey);
    printf("Decoded string: %s\n", outputBuffer);

    free(outputBuffer);
    free(tempBuffer);
    return 0;
}
