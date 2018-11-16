#ifndef __TOKENSTACK__
#define __TOKENSTACK__

#define TOKEN_STACK_SIZE 200
struct tokenStack {
  int top;
  struct lexToken *e[TOKEN_STACK_SIZE];
};

struct tokenStack *createTokenStack();
void pushTokenStack(struct tokenStack *stack, struct lexToken *token);
struct lexToken *popTokenStack(struct tokenStack *stack);
int emptyTokeStack(struct tokenStack *stack);
#endif
