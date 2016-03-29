#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "crypto-utils.h"

char hexCharToByte(char aHexChar) {
  if (aHexChar >= '0' && aHexChar <= '9') {
    return aHexChar - '0';
  }
  if (aHexChar >= 'a' && aHexChar <= 'f') {
    return (aHexChar - ('a' - 10));
  }
  printf("Failure! Invalid hex character.\n");
  exit(1);
}

// returns a malloc'd byte buffer, caller frees
char* hexStrToBytes(char* aHexStr, int* aOutLen) {
  // need valid input
  if (!aHexStr || !aOutLen) {
    return NULL;
  }

  // need an even number of hex digits to convert to bytes
  if (strlen(aHexStr) % 2 != 0) {
    return NULL;
  }

  // calculate the length of the output buffer
  *aOutLen = strlen(aHexStr) / 2;
  if (*aOutLen == 0) {
    return NULL;
  }

  // create output buffer
  char *outBuf = malloc(*aOutLen);
  if (!outBuf) {
    return NULL;
  }

  // fill the output buffer
  int inputLen = strlen(aHexStr);
  for (int i = 0; i < inputLen; i = i + 2) {
    char char1 = aHexStr[i];
    char char2 = aHexStr[i + 1];
    char byte = 0;

    byte = hexCharToByte(char1) << 4;
    byte = byte | hexCharToByte(char2);

    outBuf[i / 2] = byte;
  }
  return outBuf;
}

char* xorBuffers(char *bufferOne, char *bufferTwo, int bufferOneLen, int bufferTwoLen) {
  if (!bufferOne || !bufferTwo) {
    return NULL;
  } 

  if (bufferOneLen != bufferTwoLen) {
    return NULL;
  }

  int bufferLen = bufferOneLen;
  char *xoredBuffer = malloc(bufferLen);
  for (int i = 0; i < bufferLen; i++) {
    xoredBuffer[i] = bufferOne[i] ^ bufferTwo[i];
  }

  return xoredBuffer;
}

int scoreStr(char *str, int bytesLen) {
  int score = 0;
  for (int i = 0; i < bytesLen; i++) {
            if (isalnum(str[i])) {
                score++;
            } else if (str[i] == ' ') {
                score += 2;
            } else {
                score--;
            }
        }
  return score;
}