#include <stdio.h>
#include "trial-lang3.h"

char *tl3_read() {
  Token *token;
  while ((token = read_token()) != NULL) {
    printf("%s\n", token2string(token));
  }
  return "Hello";
}
