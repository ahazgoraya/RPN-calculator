#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexical.h"
#include "nextInputChar.h"
#include "tokenStack.h"
#include "doOperator.h"

int main(int argc, char *argv[])
{
  struct tokenStack *stack;
  struct lexToken *token;
  int ret;

  stack = createTokenStack();
  setFile(stdin);

  while(1) {
    token = nextToken();
#ifdef DEBUG
    printf("read in token "); dumpToken(stdout, token);
#endif
    switch(token->kind) {
    case LEX_TOKEN_EOF:
      exit(0);
      break;
    case LEX_TOKEN_IDENTIFIER:
    case LEX_TOKEN_OPERATOR:
      ret = doOperator(stack, token->symbol);
      freeToken(token);
      if(ret < 0)
        printf("unknown operator\n");
      break;
    case LEX_TOKEN_NUMBER:
      pushTokenStack(stack, token);
      break;
    default:
      fprintf(stderr,"unknown lex token kind %d\n", token->kind);
    }
  }
}
