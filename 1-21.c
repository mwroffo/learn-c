#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
int insert(char line[], char x, int l, int len);
int myremove(char line[], int l, int len);
void replspaces(char line[], int len, int n);

/* write a program that replaces tabs with the proper number of blanks to space to
 * the next tab stop, say every n columns. */
int main() {
    int len, n;
    char line[MAXLINE];

    n = 4; /* blanks per tab */
    while ((len = mygetline(line, MAXLINE)) > 0) {
        replspaces(line, len, n);
        printf("%s", line);
    }

    return 0;
}

/* replspaces: given a string, replace spaces with the min num of tabs + necessary spaces */
void replspaces(char s[], int len, int n) {
    int i, j, count;
    char tab = 'X';

    count = 0;
    for (i = 0; i < len; ++i) {
        if (s[i] == ' ')
            ++count;
        else count = 0; 
        if (count == n) {
            for (j = 1; j <= n; ++j) {
                len = myremove(s, i-(n-1), len);
                 
                //printf("%s", s);
            }
            len = insert(s, tab, i-(n-1), len);
            count = 0;
            i = 0;
        }
    }
}

/* getline: use getchar to read a line into s, return length which includes newline char */
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

/* insert: given string s with length len, insert char x at index l, and return new len */
int insert(char s[], char x, int l, int len) {
    if (l < 0 || l >= len) {
        printf("insert: bad arg: l=%d, len=%d\n", l, len);
        return -1;
    } 
    int high, i;
    s[len+1] = '\0'; // advance null ch to enlarge array
    for (i = len; i > l; --i) {
        s[i] = s[i-1];
    }
    s[l] = x;
    return len + 1;
}

/* remove: given string s, remove the element at index l and return the new length */
int myremove(char s[], int l, int len) {
    if (len == 0 || l < 0 || l >= len) {
        printf("remove: bad arg, index out of bounds\n");
        return -1;
    }
    
    int i;
    for (i = l; i <= len-1; ++i) {
        s[i] = s[i+1];
    }
    return len - 1;
}
