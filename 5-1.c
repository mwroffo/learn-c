// 7.21.20 TODO seems to be printing a series of addresses....

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define SIZE 10

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf

int getch(void);
void ungetch(int);

int getint(int *pn) {
  int c, sign;
  
  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
  }
  for (*pn = 0; isdigit(*pn); c = getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;

}

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

int main() {
  int n, array[SIZE], getint(int*);

  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
     ;

  for (n = 0; n < SIZE; n++) printf("%d ", array[n]);
#define SIZE 10

}
