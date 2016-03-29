#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

#define MAX_ASCII 128
#define LINE_SIZE 60
#define TOTAL_LINES 327
#define OUTPUT_LEN 30


// Compile with: gcc challenge4.c crypto-utils.c -g -o challenge4

int main(int argc, char *argv[]) {

    char *outputBuffer = malloc(OUTPUT_LEN);
    char *tempBuffer = malloc(OUTPUT_LEN);
    int maxScore = 0;
    int currentScore = 0;
    int lineNumber = 0;
    char bestGuessKey;

    FILE *fp;
    char *inputLine = (char*) malloc(sizeof(char) * LINE_SIZE);

    fp = fopen("strings.txt", "r");

    for (int i = 0; i < TOTAL_LINES; i++) {
        fscanf(fp, "%s", inputLine);

        int bytesLen = 0;
        char *inputBuffer = hexStrToBytes(inputLine, &bytesLen);

        for (unsigned int j = 0; j < MAX_ASCII; j++) {
            memset(tempBuffer, j, bytesLen);
            char *bytesXored = xorBuffers(inputBuffer, tempBuffer, bytesLen, bytesLen);
            currentScore = scoreStr(bytesXored, bytesLen);
            if (currentScore > maxScore) {
                maxScore = currentScore;
                bestGuessKey = j;
                outputBuffer = bytesXored;
                lineNumber = i;
            }
        }
    }
    fclose(fp);

    printf("Best guess key: %c\n", bestGuessKey);
    printf("Decoded string: %s\n", outputBuffer);
    printf("From line %d\n", lineNumber);

    free(outputBuffer);
    free(tempBuffer);

    return 0;
}