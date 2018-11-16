#define MAX_SYMBOL_LENGTH 129
#define LEX_TOKEN_EOF 	     1
#define LEX_TOKEN_IDENTIFIER 2
#define LEX_TOKEN_NUMBER     3
#define LEX_TOKEN_OPERATOR   4

struct lexToken {
  int kind;
  char symbol[MAX_SYMBOL_LENGTH];
};

void freeToken(struct lexToken *token);
struct lexToken *nextToken();
void dumpToken(FILE *fd, struct lexToken *token);
void printToken(FILE *fd, struct lexToken *token);
struct lexToken *allocToken();
