#include <stdio.h>
#include "trial-lang3.h"

int main() {
  Ast *ast;
  while ((ast = tl3_read()) != NULL) {
    printf("%s\n", tl3_eval(ast));
  }
  return 0;
}
