#include <stdio.h>
#include <string.h>
#include "trial-lang3.h"

Ast *tl3_eval_int(Ast *ast) {
  switch (ast->type) {
    case T:
    case NIL:
    case NUMBER:
    case SYMBOL:
      return ast;
    case CONS: {
      if (ast->car->type != SYMBOL)
        error("Symbol expected, but got %s", ast2string(ast->car));
      if (!strcmp(ast->car->sval, "print")) {
        Ast *cdr = tl3_eval_int(ast->cdr->car);
        printf("%s\n", ast2string(cdr));
        return cdr;
      }
    }
  }
  error("Internal error");
}

char *tl3_eval(Ast *ast) { return ast2string(tl3_eval_int(ast)); }
