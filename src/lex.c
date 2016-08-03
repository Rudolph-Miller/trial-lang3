#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 256

void error(char *s) {
  printf("Error: %s\n", s);
  exit(1);
}

char *tl3_read() {
  char c;
  char *buf = malloc(MAX_BUFFER_SIZE);
  int i = 0;
  while ((c = getc(stdin)) != EOF) {
    buf[i++] = c;
    if (i >= MAX_BUFFER_SIZE) {
      error("MAX_BUFFER_SIZE");
    }
  }
  buf[i] = '\0';
  return buf;
}
