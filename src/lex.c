#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 256

enum { tLPAREN, tRPAREN, tNUMBER, tSYMBOL };

typedef struct {
  int type;
  union {
    char *sval;
    int ival;
  };
} Token;

static Token *make_number(int i) {
  Token *token = malloc(sizeof(Token));
  token->type = tNUMBER;
  token->ival = i;
  return token;
}

static Token *make_lparen() {
  Token *token = malloc(sizeof(Token));
  token->type = tLPAREN;
  return token;
}

static Token *make_rparen() {
  Token *token = malloc(sizeof(Token));
  token->type = tRPAREN;
  return token;
}

static Token *make_symbol(char *s) {
  Token *token = malloc(sizeof(Token));
  token->type = tSYMBOL;
  token->sval = s;
  return token;
}

static char *token2string(Token *token) {
  switch (token->type) {
    case tLPAREN:
      return "(";
    case tRPAREN:
      return "(";
    case tNUMBER: {
      char *s = malloc(div(token->ival, 10).quot + 1);
      sprintf(s, "%d", token->ival);
      return s;
    }
    case tSYMBOL:
      return token->sval;
  }
  return NULL;
}

void error(char *s) __attribute__((noreturn));
void error(char *s) {
  printf("Error: %s\n", s);
  exit(1);
}

static Token *read_number(char c) {
  int i = c - '0';
  while ((c = getc(stdin)) != EOF && isdigit(c)) {
    i = i * 10 + c - '0';
  }
  return make_number(i);
}

static Token *read_symbol(char c) {
  char *s = malloc(MAX_BUFFER_SIZE);
  int i = 0;
  s[i++] = c;
  while ((c = getc(stdin)) != EOF) {
    s[i++] = c;
    if (i >= MAX_BUFFER_SIZE) {
      error("Symbol is too long.");
    }
  }
  s[i] = '\0';
  return make_symbol(s);
}

Token *read_token() {
  char c = getc(stdin);
  if (c == EOF) return NULL;
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return read_number(c);
    case '(':
      return make_lparen();
    case ')':
      return make_rparen();
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      return read_symbol(c);
    default:
      error("Internal error");
  }
}

char *tl3_read() {
  Token *token;
  char *buf = malloc(MAX_BUFFER_SIZE);
  int i = 0;
  while ((token = read_token()) != NULL) {
    char *s = token2string(token);
    int j = 0;
    while (s[j]) {
      buf[i++] = s[j++];
      if (i >= MAX_BUFFER_SIZE) error("MAX_BUFFER_SIZE");
    }
  }
  buf[i] = '\0';
  return buf;
}
