#include <stdio.h>
#define MAXLINE 1000
#define LOWER_BOUND 5

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* Write a program to print all input lines that are longer than LOWER_BOUND characters */
int main() {

    int len;
    char line[MAXLINE];

    while ((len = mygetline(line, MAXLINE)) > 0)
        if (len > LOWER_BOUND) {
            printf("%s", line);
        }

    return 0;
}

/* getline: use getchar to read a line into s, return length */
int mygetline(char s[], int lim) {
    int c, i;
    // Q: Why do we make lim-2 the upper bound index?
    // A: To leave room for the newline char.
    for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;
    // Q: Why do we care about the newline char? 
    // A: To distinguish between complete lines and truncated lines.
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    // Q: Why do we need to manually insert the null char?
    // A: To strip unnecessary length from the array.
    s[i] = '\0';
    return i;
}

/* copy: copy elements from `from` into `to` */
void copy(char to[], char from[]) {
    int i;

    i = 0;
    /* assume `to` is large enough */
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
