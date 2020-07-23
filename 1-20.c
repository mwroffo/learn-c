/* Exercise 1-20:
Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume a fixed set of tab stops,
say every n columns. Should n be a variable or a symbolic parameter? 
*/

#include <stdio.h>

int main(void) {
    int i = 10;
    int* ip;
    ip = &i;
    *ip=11;
    ++i;
    ++*ip;
    (*ip)++; // Q: Explain why the parenthesis are necessary.
             // A: Unary operators associate right to left.
    printf("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n");
    printf("0 1 2 3 4 5 6 7 8 9  A  B  C  D  E  F\n");
    printf("%0X\n",*ip);

    printf("hello there, \f");
}
