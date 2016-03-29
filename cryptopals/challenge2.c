#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"


// Compile with: gcc challenge2.c crypto-utils.c -g -o challenge2

static char *sInputStrOne = "1c0111001f010100061a024b53535009181c";

static char *sInputStrTwo = "686974207468652062756c6c277320657965";

static char *sOutputStr = "746865206b696420646f6e277420706c6179";


int main(int argc, char *argv[]) {

    int bytesLenOne = 0;
    int bytesLenTwo = 0;
    int outputBytes = 0;

    char *bufferOne = hexStrToBytes(sInputStrOne, &bytesLenOne);
    char *bufferTwo = hexStrToBytes(sInputStrTwo, &bytesLenTwo);

    char *outputBuffer = hexStrToBytes(sOutputStr, &outputBytes);

    char *bytes = xorBuffers(bufferOne, bufferTwo, bytesLenOne, bytesLenTwo);

    if (strcmp(bytes, outputBuffer) == 0) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }

    free(bytes);

    return 0;
}