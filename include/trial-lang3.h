#ifndef TRIAL_LANG_3__

#define MAX_BUFFER_SIZE 256

#define error(...) errorf(__FILE__, __LINE__, __VA_ARGS__)
void errorf(char *file, int line, char *fmt, ...) __attribute__((noreturn));

typedef struct {
  char *body;
  int nalloc;
  int len;
} String;

String *make_string();
char *get_cstring(String *s);
void string_append(String *s, char c);
void string_appendf(String *s, char *fmt, ...);

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

enum {
  T,
  NIL,
  NUMBER,
  SYMBOL,
  CONS,
};

typedef struct Ast {
  int type;
  union {
    // Number
    int ival;
    // Symbol
    char *sval;
    // Cons
    struct {
      struct Ast *car;
      struct Ast *cdr;
    };
  };
} Ast;

char *ast2string(Ast *ast);
Ast *tl3_read();

#endif
