#include <stdio.h>
#include <stdlib.h>
#include "nextInputChar.h"

static FILE *fd;
static int lastChar = -1;

void setFile(FILE *d)
{
  fd = d;
}

int getChar()
{
  if(lastChar >= 0) {
    int temp = lastChar;
    lastChar = -1;
    return temp;
  }
  if(feof(fd))
    return -1;
  return fgetc(fd);
}

void ungetChar(int ch)
{
  if(lastChar >= 0) {
    fprintf(stderr,"ungetChar: max pushback is one character\n");
    exit(1);
  }
  if(ch < 0) {
    fprintf(stderr,"ungetChar: trying to push back a negative character\n");
    exit(1);
  }
  lastChar = ch;
}

