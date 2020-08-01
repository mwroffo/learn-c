#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
int insert(char line[], char x, int l, int len);
int myremove(char line[], int l, int len);
void printlines(char line[], int len, int n);

/* "fold" long input lines into two or more shorter lines after the last 
 * non-blank char before the nth column of input. must handle very long 
 * lines, and account for the case of no blanks or tabs before the 
 * specified column. */
int main() {
    int len, n;
    char line[MAXLINE];
    
    n = 79; /* max printline length */
    while ((len = mygetline(line, MAXLINE)) > 0) {
        printlines(line, len, n);
        printf("%s", line);
    }

    return 0;
}

/* printlines: given a char[] line of length len, for each subline of length n, print subilne. */
void printlines(char s[], int len, int n) {
    int i, li, count;
    char c, lastchar;
    c = s[i];
    count = 0; // always initialize counters manually
    for (i = 0; i < len; ++i) {
        if ( !(c==' ' || c=='\t' || c=='\n' || c==',' || c==';' || c=='.') ) {
            lastchar = c;
            li = i;
        }
        ++count;
        if (count == n) {
            len = insert(s, '\n', li+1, len);
            count = i - (li+1); // reset colcount
            ++i; // because length increased
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
