/*
 * 07.22.20
 * Write a program that prints input, replacing each string of one or more
 * blanks by a single blank,
 * 
 */

#include <stdio.h>

#define IN 1
#define OUT 0

main() {
  int c, state;
  state = OUT;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) 
        putchar(c);
      state = OUT;
    } else {
      if (state == OUT) 
        state = IN;
      putchar(c);
    }
  }
}

