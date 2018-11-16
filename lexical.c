#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"
#include "nextInputChar.h"

#define STATE_S1  1
#define STATE_S2  2
#define STATE_S3  3
#define STATE_S4  4

/* function to allocate a new token */
struct lexToken *allocToken()
{
  struct lexToken *token;

  if((token = (struct lexToken *) malloc(sizeof(struct lexToken))) == (struct lexToken *)NULL) {
    fprintf(stderr,"nextToken: out of memory, aborting\n");
    exit(1);
  }
  token->symbol[0] = '\0';
  return token;
}


void freeToken(struct lexToken *token)
{
  (void) free(token);
}

void dumpToken(FILE *fd, struct lexToken *token)
{
  if(token == (struct lexToken *) NULL)
    fprintf(fd, "dumpToken: null token\n");
  else {
    switch(token->kind) {
    case LEX_TOKEN_EOF :
      fprintf(fd, "dumpToken: EOF token\n");
      break;
    case LEX_TOKEN_IDENTIFIER:
      fprintf(fd, "dumpToken: identifier token |%s|\n", token->symbol);
      break;
    case LEX_TOKEN_OPERATOR:
      fprintf(fd, "dumpToken: operator token |%s|\n", token->symbol);
      break;
    case LEX_TOKEN_NUMBER:
      fprintf(fd, "dumpToken: number token |%s|\n", token->symbol);
      break;
    default:
      fprintf(fd, "dumpToken: bad token type %d\n", token->kind);
    }
  }
}


void printToken(FILE *fd, struct lexToken *token)
{
  if(token == (struct lexToken *) NULL)
    fprintf(fd, "null\n");
  else {
    switch(token->kind) {
    case LEX_TOKEN_EOF :
      fprintf(fd, "EOF\n");
      break;
    case LEX_TOKEN_IDENTIFIER:
    case LEX_TOKEN_OPERATOR:
    case LEX_TOKEN_NUMBER:
      fprintf(fd, "%s\n", token->symbol);
      break;
    default:
      fprintf(fd, "dumpToken: bad token type %d\n", token->kind);
    }
  }
}

struct lexToken *nextToken() 
{
  int c;
  struct lexToken *token;
  int symbolLength;
  int state = STATE_S1;

  token = allocToken();
  while(1) {
    switch(state) {
    case STATE_S1:
      switch(c = getChar()) {
      case -1: /* EOF */
        token->kind = LEX_TOKEN_EOF;
        return token;
      case ' ':
      case '\t':
      case '\n':
        break;
      case '/':
      case '*':
        token->symbol[0] = c;
        symbolLength = 1;
        state = STATE_S3;
        break;
      default:
        if(((c >= 'a') && (c <='z'))||((c >= 'A') && (c <= 'Z'))) {
          token->symbol[0] = c;
          symbolLength = 1;
          state = STATE_S2;
        } else if((c == '+')||(c == '-')||((c >= '0') && (c <= '9'))) {
          token->symbol[0] = c;
          symbolLength = 1;
          state = STATE_S4;
        } else 
          fprintf(stderr,"nextToken: bad char %c in input stream, ignored\n",c);
      }
      break;
    case STATE_S2: /* identifier */
      c = getChar();
      if(((c >= 'a') && (c <= 'z'))||((c >= 'A') && (c <= 'Z'))) {
        if(symbolLength == MAX_SYMBOL_LENGTH-1) {
          fprintf(stderr,"nextToken: symbol too long, aborting\n");
          exit(1);
        }
        token->symbol[symbolLength++] = c;
      } else {
       ungetChar(c);
       token->kind = LEX_TOKEN_IDENTIFIER;
       token->symbol[symbolLength] = '\0';
       return token;
      }
      break;
    case  STATE_S3: /* operator */
      token->kind = LEX_TOKEN_OPERATOR;
      token->symbol[symbolLength] = '\0';
      return token;
    case STATE_S4: /* number */
      c = getChar();
      if((c >= '0') && (c <= '9')) {
        if(symbolLength == MAX_SYMBOL_LENGTH-1) {
          fprintf(stderr,"nextToken: symbol too long, aborting\n");
          exit(1);
        }
        token->symbol[symbolLength++] = c;
      } else {
        ungetChar(c);
        if((symbolLength == 1) && ((token->symbol[0] == '-')||(token->symbol[0] == '+')))
          token->kind = LEX_TOKEN_OPERATOR;
        else
          token->kind = LEX_TOKEN_NUMBER;
        token->symbol[symbolLength] = '\0';
        return token;
      }
      break;
    default:
      fprintf(stderr,"nextToken: can't happen\n");
      exit(1);
    }
  }
}
