#include <stdio.h>
#include <stdlib.h>
#include "trial-lang3.h"

static Ast *t = &(Ast){T};
static Ast *nil = &(Ast){NIL};

Ast *ast_t() { return t; }

Ast *ast_nil() { return nil; }

Ast *ast_number(int i) {
  Ast *ast = malloc(sizeof(Ast));
  ast->type = NUMBER;
  ast->ival = i;
  return ast;
}

Ast *ast_symbol(char *s) {
  Ast *ast = malloc(sizeof(Ast));
  ast->type = SYMBOL;
  ast->sval = s;
  return ast;
}

Ast *ast_cons(Ast *car, Ast *cdr) {
  Ast *ast = malloc(sizeof(Ast));
  ast->type = CONS;
  ast->car = car;
  ast->cdr = cdr;
  return ast;
}

char *ast2string(Ast *ast) {
  switch (ast->type) {
    case T:
      return "T";
    case NIL:
      return "NIL";
    case NUMBER: {
      char *s = malloc(div(ast->ival, 10).quot + 1);
      sprintf(s, "%d", ast->ival);
      return s;
    }
    case SYMBOL:
      return ast->sval;
    case CONS: {
      String *s = make_string();
      string_appendf(s, "(%s . %s)", ast2string(ast->car),
                     ast2string(ast->cdr));
      return get_cstring(s);
    }
  }
  error("Internal error");
}

Ast *tl3_read() {
  Token *token = read_token();
  if (!token) return NULL;
  switch (token->type) {
    case tNUMBER:
      return ast_number(token->ival);
    case tLPAREN: {
      token = peek_token();
      if (token->type == tRPAREN) return ast_cons(nil, nil);
      Ast *car = tl3_read();
      token = peek_token();
      if (token->type == tRPAREN) return ast_cons(car, nil);
      Ast **buffer = malloc(sizeof(Ast *) * MAX_BUFFER_SIZE);
      int i = 0;
      buffer[i++] = car;
      while (peek_token()->type != tRPAREN) {
        if (peek_token() == NULL) error("Parens not correctly closed");
        buffer[i++] = tl3_read();
        if (i == MAX_BUFFER_SIZE) error("Too long list");
      }
      read_token();
      buffer[i] = nil;
      for (; i > 0; i--) {
        buffer[i - 1] = ast_cons(buffer[i - 1], buffer[i]);
      }
      return buffer[0];
    }
    case tSYMBOL: {
      return ast_symbol(token->sval);
    }
  }
  error("Internal error");
}
