#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trial-lang3.h"

#define MAX_BUFFER_SIZE 256

Token *ungotten = NULL;

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

char *token2string(Token *token) {
  if (!token) error("Token is NULL");
  switch (token->type) {
    case tLPAREN:
      return "(";
    case tRPAREN:
      return ")";
    case tNUMBER: {
      char *s = malloc(div(token->ival, 10).quot + 1);
      sprintf(s, "%d", token->ival);
      return s;
    }
    case tSYMBOL:
      return token->sval;
  }
  error("Invalid token");
}

static Token *read_number(char c) {
  int i = c - '0';
  while ((c = getc(stdin)) != EOF && isdigit(c)) {
    i = i * 10 + c - '0';
  }
  if (c) ungetc(c, stdin);
  return make_number(i);
}

static Token *read_symbol(char c) {
  char *s = malloc(MAX_BUFFER_SIZE);
  int i = 0;
  s[i++] = c;
  while ((c = getc(stdin)) != EOF && !isspace(c)) {
    s[i++] = c;
    if (i >= MAX_BUFFER_SIZE) {
      error("Too long symbol");
    }
  }
  s[i] = '\0';
  return make_symbol(s);
}

char getc_without_spaces() {
  char c;
  while ((c = getc(stdin)) != EOF) {
    if (isspace(c) || c == '\r' || c == '\n') continue;
    return c;
  }
  return EOF;
}

Token *read_token() {
  if (ungotten) {
    Token *token = ungotten;
    ungotten = NULL;
    return token;
  }
  char c = getc_without_spaces();
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
      error("Invalid character for Token: %c", c);
  }
}

void unread_token(Token *token) {
  if (ungotten) error("Already ungotten token: %s", token2string(ungotten));
  ungotten = token;
}

Token *peek_token() {
  Token *token = read_token();
  unread_token(token);
  return token;
}
