#include <stdio.h>
#include <stdlib.h>
#include "tokenStack.h"

struct tokenStack *createTokenStack()
{
  struct tokenStack *stack;

  if((stack = (struct tokenStack *)malloc(sizeof(struct tokenStack))) == (struct tokenStack *)NULL) {
    fprintf(stderr,"createTokenStack: out of memory, aborting\n");
    exit(1);
  }
  stack->top = 0;
  return stack;
}

void pushTokenStack(struct tokenStack *stack, struct lexToken *token) {
  if(stack->top == TOKEN_STACK_SIZE) {
    fprintf(stderr, "pushTokenStack: out of stack space, aborting\n");
    exit(1);
  }
  stack->e[stack->top++] = token;
}

struct lexToken *popTokenStack(struct tokenStack *stack) {
  if(stack->top <= 0) {
    fprintf(stderr,"popTokenStack: popping an empty stack, aborting\n");
    exit(1);
  }
  return stack->e[--(stack->top)];
}

int emptyTokenStack(struct tokenStack *stack)
{
  return stack->top == 0;
}
