#include <stdio.h>
#include "lexical.h"
#include "nextInputChar.h"

/* lexTester.c */

int main(int argc, char *argv[])
{

  setFile(stdin);
  while(1) {
    struct lexToken *token;

    token = nextToken();
    dumpToken(stdout, token);
    if(token->kind == LEX_TOKEN_EOF)
      break;
    freeToken(token);
  }
}
