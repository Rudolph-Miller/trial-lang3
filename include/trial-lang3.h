#ifndef TRIAL_LANG_3__

#define error(...) errorf(__FILE__, __LINE__, __VA_ARGS__)
void errorf(char *file, int line, char *fmt, ...) __attribute__((noreturn));

enum { tLPAREN, tRPAREN, tNUMBER, tSYMBOL };

typedef struct {
  int type;
  union {
    char *sval;
    int ival;
  };
} Token;

Token *read_token();
void unread_token(Token *token);
Token *peek_token();
char *token2string(Token *token);

char *tl3_read();

#endif
