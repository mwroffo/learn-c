#include <stdio.h>
#define MAXLINE 1000
#define OUT 0
#define IN 1
/* dont print lines of len < 1 */
#define LB 1

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {

    int len;
    char line[MAXLINE];

    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > LB)
            for (int j=0; j<len; ++j) {
                printf("%c", line[j]);
                line[j] = 0;
            }
    }

    return 0;
}

/* getline: read a line into s, sanitize it, return length */
int mygetline(char s[], int lim) {
    int c, i, state;
    // Q: Why do we make lim-2 the upper bound index?
    // A: To leave room for the newline char.
    state = OUT;
    for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i) {
        if (c == ' ' || c == '\t') {
            if (state == IN)
                s[i] = ' ';
            state = OUT;
        } else {
            state = IN;
            s[i] = c;
        }

        // printf("%4d %c %d %s\n",i,c,state,s);
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    // Q: Why do we need to manually insert the null char?
    // A: To strip unnecessary length from the array.
    s[i] = '\0';
    // printf("s: ");
    // for (int j=0; j<i; ++j) printf("%c", s[j]);

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
