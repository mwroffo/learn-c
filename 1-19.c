#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
void reverse(char line[], int len);
void swap(char v[], int i, int j);

/* write a function reverse(s) that reverses that character string s. Use it to write a program that reverses its input a line at a time. */
int main() {
    int len;
    char line[MAXLINE];

    while ((len = mygetline(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s", line);
    }

    return 0;
}

/* reverse(s): given a string, reverse its order */
void reverse(char s[], int len) {
    int low, high;
     
    low = 0;
    high = len - 2; /* begin before the newline char */
    while (low < high) {
        swap(s, low++, high--);
    }
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
