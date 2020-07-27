#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
void repltabs(char line[], int len, int n);
void swap(char v[], int i, int j);

/* write a function reverse(s) that reverses that character string s. Use it to write a program that reverses its input a line at a time. */
int main() {
    int len, n;
    char line[MAXLINE];

    n = 4; /* blanks per tab */
    while ((len = mygetline(line, MAXLINE)) > 0) {
        repltabs(line, len, n);
        printf("%s", line);
    }

    return 0;
}

/* repltabs(s): given a string, replace its tabs with n blanks */
void repltabs(char s[], int len, int n) {

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

void swap(char v[], int i, int j) {
    char temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
