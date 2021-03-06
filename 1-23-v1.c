#include <stdio.h>
#define MAXLINE 1000
#define OUT 0
#define IN 1

int mygetline(char line[], int maxline);
int myremove(char line[], int l, int len);
int myremoverange(char line[], int low, int high, int len);
int rmcommline(char line[], int len);
int rmslashstar(char line[], char *state, int len);
int rmcomments(char line[], char *state, int len);
int myiswhitespace(char line[], int len);

/* Write a program to remove all comments from a C program. Handle character
    constants 'c' and "strings" properly. Should also work with the multiline comment.
*/
int main() {
    int len;
    char state, line[MAXLINE];

    state = OUT;
    while ((len = mygetline(line, MAXLINE)) > 0)
    {
        len = rmcomments(line, &state, len);
        if (len > 0)
            printf("%s", line);
    }

    return 0;
}

// given line s with length len, remove comments then return updated len.
int rmcomments(char s[], char *state, int len) {
    len = rmcommline(s, len);
    len = rmslashstar(s, state, len);
    if (!(myiswhitespace(s, len)))
        return len;
    else return 0;
}

// given line s, state pointer, and len, remove chars that are part of a
// slashstar comment, update state, and return new len.
int rmslashstar(char s[], char *state, int len) {
    int i, lb, ub;
    char c, prevc;
    
    ub = len-1;
    lb = prevc = 0;
    for (i = 0; i < len; ++i) {
        c = s[i];

        if (c == '*' && prevc == '/' && *state == OUT) {
            *state = IN;
            lb = i - 1;
        }
        if (c == '/' && prevc == '*' && *state == IN) {
            *state = OUT;
            ub = i + 1;
            len = myremoverange(s, lb, ub, len);
        }

        prevc = c;
    }

    if (*state == IN) // if we are still inside a comment, delete up to end of line
        len = myremoverange(s, lb, ub = len - 1, len);
    
    return len;
}

int rmcommline(char s[], int len) {
    int i;
    char c, prevc, state;
    
    prevc = 0;
    i = 0;
    state = OUT;
    while (i < len-1) {
        if (s[i] == '/' && prevc == '/' && state == OUT) { // && state == OUT
            state = IN;
            i--;
        }
        if (state == IN) {
            // printf("%s", s);
            len = myremove(s, i, len);
        } else {
            prevc = s[i];
            ++i;
        }
    }
    return len;
}

/* getline: use getchar to read a line into s, return length which includes newline char */
int mygetline(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* myremove: given string s, remove the element at index l and return the new length */
int myremove(char s[], int l, int len) {
    if (len == 0 || l < 0 || l >= len) {
        printf("myremove: bad arg, index out of bounds: l==%d, len==%d\n", l, len);
        return -1;
    }
    
    int i;
    for (i = l; i <= len-1; ++i) {
        s[i] = s[i+1];
    }
    return len - 1;
}

// myremoverange: given string s with length len, remove elements in the range [low, high).
int myremoverange(char s[], int low, int high, int len)
{

    if (len == 0 || low < 0 || low >= len || high < 0 || high > len)
    {
        printf("myremoverange: bad arg:\n%s\n\n\tlen=%d\n\tlow=%d\n\thigh=%d\n", s, len, low, high);
        return -1;
    }
    int i;

    i = low;
    while (i < high)
    {
        len = myremove(s, low, len);
        ++i;
    }
    return len;
}

// myiswhitespace: given line s, return 1 if s contains only ' ', '\t',
// and '\n', else return 0.
int myiswhitespace(char s[], int len)
{
    int i;
    char c;

    for (i = 0; i < len; ++i)
    {
        c = s[i];
        if (!(c == ' ' || c == '\t' || c == '\n'))
        {
            return 0;
        }
    }
    return 1;
}