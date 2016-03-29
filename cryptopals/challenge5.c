#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

#define HEX_PER_BYTE 2

// Compile with: gcc challenge5.c crypto-utils.c -g -o challenge5

static char *sInputStr = "Burning 'em, if you ain't quick and nimble\n"
                         "I go crazy when I hear a cymbal";

static char *sOutputStr = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272"
                          "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

static char *sKEY = "ICE";

int main(int argc, char *argv[]) {

    char *outputBuffer = (char*) malloc(sizeof(char) * strlen(sInputStr) * 2);

    for (int i = 0; i < strlen(sInputStr); i++) {
        char xoredChars = sInputStr[i] ^ sKEY[i % strlen(sKEY)];
        sprintf(outputBuffer + (i * HEX_PER_BYTE), "%02x", xoredChars);
    }
    
    if (strcmp(outputBuffer, sOutputStr) == 0) {
        printf("Success!\n");
    } else {
        printf("Fail!\n");
    }

    if (argc > 1 && strcmp(argv[1], "-p") == 0) {
        printf("%s\n", outputBuffer);
    }

    free(outputBuffer);
    return 0;
}