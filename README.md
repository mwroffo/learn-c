# learn-c

My exercise notes as I work through "The C Programming Language (2nd Ed.) by Kernighan and Ritchie.

## Table of Contents
1. Ex 1-23
    a. (Second solution)[##ex1-23] (more elegant, less coupled. uses pointers.)
    b. (First solution)[##ex1-23firstattempt]

## Ex 1-23

While my first solution (see below) for this exercise was unnecessarily coupled, by using pass-by-pointer in this solution, we enable the `rmslashstar` function to stick to its purpose ([SRP](https://en.wikipedia.org/wiki/Single-responsibility_principle)) if removing slash-star style comments from a given line, while `main` handles the reading of lines.

In pseudocode:
```
mainroutine {
    while (there is another line from stdin) {
        remove the comments
        print the line
    }
}

subroutine remove the comments {
    given line, remove the slashslash comments
    given line, remove the slashstar comments
    having updated line, return len
}

subroutine remove the slashslash comments {
    given line, iterate through chars. if two chars in a row, then update state, delete through the end of the line, stopping before the \n. Return new len.
}

subroutine remove the slashstar comments {
    given line, state pointer, and len, remove chars that are part of comment,
        update state, finally return new len.
}
```

Full program:

```
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
```

## Ex 1-23 (first attempt)

This particular application of state-aware text processing isn't as interesting as the generalization it exemplifies:  As we iterate through a collection, how can we gather information, then leverage that information for effective control flow? How can we effectively store, represent, and act on state information? Can an iterating function make decisions based on previous (easy) or (harder) forthcoming characters?

In this case of removing comments from every line of the program, we must determine, given line `char s[]`, what range(s) of indices in `s` are comments, so we can remove them.

Comments in the double-slash style are easy to remove, because once we have two slashes in a row, we simply delete the rest of the line.

But comments in the slash-star style are harder to identity, because they must be closed explicitly and can encompass multiple lines. While double-slash comments can safely be removed character by character after the double-slash, in the slash-star case, we don't know whether the current character `curr` is safe to delete, not until we are already past `curr`.

Then let's proceed by determining the range to be removed, then executing the removal, rather than trying to remove comment-characters as we iterate.   

Implement this helper function:
```
// myremoverange: remove from s elems in the range [lo,hi) and return the new length.
int myremoverange(char s[], int low, int high, int len) {
    if (len == 0 || low < 0 || low >= len || high < 0 || high > len) {
        printf("myremoverange: bad arg:\n%s\n\n\tlen=%d\n\tlow=%d\n\thigh=%d\n", s, len, low, high);
        return -1;
    }

    int i;

    i=low;
    while (i < high) {
        len = myremove(s, low, len);
        ++i;
    }
    return len;
}
```
where myremove removes the elem at low from the array s, returning the new length.

Now that we have a tool for removing a range of chars from a line, our line traversal's only job is to determine the bounds of the subarray to be removed. Then we call myremoverange after the loop.

Let's start by declaring a function that removes double-slash comments from a given line: `int rmcommline(char line[], int len);`, saving the new line in the argument `line` and returning the new length as `int`.

And it must succeed for any of these given cases, where a case is a given line of characters, followed by a newline `\n`.

Case 0
```
// Huxley, _Brave New World_.

```

Case 1
```
printf("hello world\n");

```

Case 2
```
printf("hello world\n"); // MacDonald */ George

```

Case 3
```
// printf("hello world\n"); // George MacDonald

```

## identify-range-to-delete-then-delete-range approach

Version 1:
```
int rmcommline(char s[], int len) {
    int i, lb, ub;
    char c, prevc;

    lb = 0;
    prevc = 0;
    for (i = 0; i < len; ++i) {
        c = s[i];
        if (c == '/' && prevc == '/') {
            lb = i-1;
        }
    }
    len = myremoverange(s, lb, len-1, len);
    return len;
}
```
outputs
```
for (i = 0; i < len; ++i) {
    printf("%s\n", "Summer, state your deal.");
}
```
Excellent. It even removes the newlines left by the removed comments on each line. Let's try another example:

Example 2
```
for (i = 0; i < len; ++i) {
    printf("%s\n", "Summer, state your deal."); // the tears,
}
```
Uh oh, the program deleted the lines that do not contain comments. What is going on?

Notice how Version 1 initializes the lower-bound `lb` as 0? Lines without a "//" have their lb updated, so the entire line is deleted. We might try initializing `lb` as some more harmless value, like `lb = len-1`, which gives Version 2 of `rmcommline`.

Version 2
```
int rmcommline(char s[], int len) {
    int i, lb;
    char c, prevc;

    lb = len-1;
    prevc = 0;
    for (i = 0; i < len; ++i) {
        c = s[i];
        if (c == '/' && prevc == '/') {
            lb = i-1; 
        }
        prevc = c;
    }
    len = myremoverange(s, lb, len - 1, len);
    return len;
}
```

Now by `./a.out < ex4` we get
```
for (i = 0; i < len; ++i) {
    printf("hello world\n"); 
}
```
as desired.

But given Example 5:
```
int main() {
    // printf("hello world\n"); // Lewis
    return 0;
}
```

when we try `./a.out < ex5` we get
```
int main() {
    // printf("hello world\n");
    return 0;
}
```
where we wanted
```
int main() {
    return 0;
}
```
Okay, given a nested comment, our program got confused into thinking that the first comment wasn't a real comment. We need to make our program a little smarter than that. To do so, we introduce the notion of __state__: according to [technopedia](https://www.techopedia.com/definition/696/state-computer-science), a program's state consists of its variables and constants. Sometimes programmers use a variable explicitly called `state` to store crucial info about what situation the program is in. This variable could be as small as a single boolean variable, or it could be a vast data structure encapsulating numerous fields. Either way the program can prompt this variable when making control flow decisions.

In our specific case, our program entered a comment `b` when it was already inside a comment `a`, causing it to disregard `a` and fail to remove `a` from the input.

Then let's add a variable `char state` to store whether the program is or is not already inside a comment. We will move the call to `myremoverange` out of the `if (c == '/' && prevc == '/')` condition, because we don't want it called for every `//` that appears. We only want it called when we are (1) inside a comment, and (2) we have reached the end of the line `s`. So we place it after the loop, under the condition that `state == IN`.

```
int rmcommline(char s[], int len) {
    int i, lb, ub;
    char c, prevc, state;

    lb = len-1;
    prevc = 0;
    for (i = 0; i < len; ++i)
    {
        c = s[i];
        if (c == '/' && prevc == '/')
        {
            lb = i - 1;
            state = IN;
        }
        prevc = c;
    }
    if (state == IN)
        len = myremoverange(s, lb, len - 1, len);
    return len;
}
```
Running `./a.out < ex5` outputs
```
int main() {
    // printf("hello world\n");
    return 0;
}
```
Whoops, we thought this would fix it. But have another look at our control flow: It says: if `if (c == '/' && prevc == '/')`, then assign the lower bound and set state to inside, no matter what what we are currently in. Then if we are iterating through our string and state has already been set to IN, the program would just update the lower bound and set state to IN, again, producing the same bug as before.

Fix this by specifying that state must be OUT in order to update the lower bound and set state to IN.

```
int rmcommline(char s[], int len) {
    int i, lb, ub;
    char c, prevc, state;

    lb = len-1;
    prevc = 0;
    state = OUT;
    for (i = 0; i < len; ++i)
    {
        c = s[i];
        if (c == '/' && prevc == '/' && state == OUT)
        {
            lb = i - 1;
            state = IN;
        }
        prevc = c;
    }
    if (state == IN)
        len = myremoverange(s, lb, len - 1, len);
    return len;
}
```
Now running `./a.out < ex5` outputs
```
int main() {

    return 0;
}
```
just like we wanted.





## Time Complexity enhancementt: from `O(2n)` to `O(n)`
But in this determine-range-to-delete-then-delete approach, we have to iterate through the array twice, giving `O(2n)`. Alternatively we can mark the lower bound and delete in the first iteration to get `O(n)` time.

Let's try to implement this delete-as-we-go approach by decrementing `i` to the first slash upon finding the second slash in a row, (i.e. upon confirming that we've entered a comment.) then deleting chars until the loop exits.
```
// case0: FAIL
// case1: PASS
// case2: FAIL
// case3: FAIL
int rmcommline(char s[], int len) {
    int i, lb, ub;
    char c, prevc, state;

    prevc=0;
    i=0;
    state = OUT;
    while (i < len-1) {
        if (s[i] == '/' && prevc == '/') {
            state = IN;
            i--;
        }
        if (state == IN) {
            printf("%s",s);
            len = myremove(s, i, len);
        } else {
            ++i;
        }
        prevc = s[i];
    }
    return len;
}
```
yields
```
$ ./a.out < case2
printf("hello world\n"); // MacDonald George
printf("hello world\n");// MacDonald George
printf("hello world\n")// MacDonald George
printf("hello world\n"// MacDonald George
printf("hello world\n// MacDonald George
printf("hello world\// MacDonald George
printf("hello world// MacDonald George
printf("hello worl// MacDonald George
printf("hello wor// MacDonald George
printf("hello wo// MacDonald George
printf("hello w// MacDonald George
printf("hello // MacDonald George
printf("hello// MacDonald George
printf("hell// MacDonald George
printf("hel// MacDonald George
printf("he// MacDonald George
printf("h// MacDonald George
printf("// MacDonald George
printf(// MacDonald George
printf// MacDonald George
print// MacDonald George
prin// MacDonald George
pri// MacDonald George
pr// MacDonald George
p// MacDonald George
// MacDonald George
myremove: bad arg, index out of bounds: l==-1, len==20
```
Case 2 is the most instructive of what's going on. `myremove` is doing backward-deletes whereas we want forward deletes. Can you see why it is doing the former? Since `prevc = s[i];` is executed on every loop, aaaaand since the backward-delete makes `s[i]` always the same char (even as `i` decrements)... then `s[i] == '/' && prevc == '/'` is true on every iteration, so that `i` decrements infinitely, cheerfully deleting stuff from your program's hapless runtime stack (hopefully nothing important). This situation exemplifies [undefined behavior](https://stackoverflow.com/questions/1239938/accessing-an-array-out-of-bounds-gives-no-error-why), which is worse than your program crashing.

To fix this let's try setting `prevc = 0` after setting state to `IN`. This way the conditional `s[i] == '/' && prevc == '/'` which causes `i` to decrement won't be triggered more than once, as desired. And let's move `prevc = s[i]` into the else clause with `++i` so that prevc is only updated when state is OUT.

Now we have
```
int rmcommline(char s[], int len) {
    int i;
    char c, prevc, state;

    prevc = 0;
    i = 0;
    state = OUT;
    while (i < len-1) {
        if (s[i] == '/' && prevc == '/') {
            state = IN;
            i--;
            prevc = 0;
        }
        if (state == IN) {
            printf("%s", s);
            len = myremove(s, i, len);
        } else {
            ++i;
            prevc = s[i];
        }
    }
    return len;
}
```
Now we have
```
_mexus@kingOfRedLions:learn-c (master) $ ./a.out < case2
printf("hello world\n"); // MacDonald George
printf("hello world\n");// MacDonald George
printf("hello world\n");/ MacDonald George
printf("hello world\n"); MacDonald George
printf("hello world\n");MacDonald George
printf("hello world\n");acDonald George
printf("hello world\n");cDonald George
printf("hello world\n");Donald George
printf("hello world\n");onald George
printf("hello world\n");nald George
printf("hello world\n");ald George
printf("hello world\n");ld George
printf("hello world\n");d George
printf("hello world\n"); George
printf("hello world\n");George
printf("hello world\n");eorge
printf("hello world\n");orge
printf("hello world\n");rge
printf("hello world\n");ge
printf("hello world\n");e
OUTPUT: printf("hello world\n");
```
That's better.

Let's try it with case3:
```
_mexus@kingOfRedLions:learn-c (master) $ ./a.out < case3
// printf("hello world\n"); // George MacDonald
/ printf("hello world\n"); // George MacDonald
 printf("hello world\n"); // George MacDonald
printf("hello world\n"); // George MacDonald
rintf("hello world\n"); // George MacDonald
intf("hello world\n"); // George MacDonald
ntf("hello world\n"); // George MacDonald
tf("hello world\n"); // George MacDonald
f("hello world\n"); // George MacDonald
("hello world\n"); // George MacDonald
"hello world\n"); // George MacDonald
hello world\n"); // George MacDonald
ello world\n"); // George MacDonald
llo world\n"); // George MacDonald
lo world\n"); // George MacDonald
o world\n"); // George MacDonald
 world\n"); // George MacDonald
world\n"); // George MacDonald
orld\n"); // George MacDonald
rld\n"); // George MacDonald
ld\n"); // George MacDonald
d\n"); // George MacDonald
\n"); // George MacDonald
n"); // George MacDonald
"); // George MacDonald
); // George MacDonald
; // George MacDonald
 // George MacDonald
// George MacDonald
/ George MacDonald
 George MacDonald
George MacDonald
eorge MacDonald
orge MacDonald
rge MacDonald
ge MacDonald
e MacDonald
 MacDonald
MacDonald
acDonald
cDonald
Donald
onald
nald
ald
ld
d
OUTPUT:
```

It's not the easiest output to understand, but the line reduces to nothing by the end, which is exactly what we want because the entire input line was a comment.

While this gets the job done, the code would be less confusing to read we didn't use `prevc` in this way. As its name suggests, it is supposed to hold the previous char, but in fact it holds nothing so long as state == IN. Since modern computers have plenty of memory overhead, let's guiltlessly declare a variable for this exact purpose. Let `char state` be `IN` if we are inside a comment and `OUT` if we are outside a comment. Now we can solve our previous problem of `i` decrementing infinitely in a different way. Let's adjust our `s[i] == '/' && prevc == '/'` conditional to run only when we are not already in a comment: i.e. when `s[i] == '/' && prevc == '/' && state == OUT`. Now we have

```
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
            printf("%s", s);
            len = myremove(s, i, len);
        } else {
            prevc = s[i++];
        }
    }
    return len;
}
```
We get the same results, and its easier to read. In general it's wise to give an object only [one job](https://en.wikipedia.org/wiki/Single-responsibility_principle).





Example 3
```
for (i = 0; i < len; ++i) { // Christianity without
    /* Wherefore doth the
    way of the
    wicked prosper? 
    (Jeremiah 12:1) */
    printf("%s\n", "Summer, state your deal."); // the tears,
} // that's what soma is.
// Aldous Huxley, _Brave New World_.
```
we get 
```
for (i = 0; i < len; ++i) {

    printf("%s\n", "Summer, state your deal.");
}
```
which, while eliminating the comments, retains an empty line we perhaps don't want. Since this fixes Example 2's bug so cheaply, we will be flexible with this requirement.

--

Example 5
```
int main() {
    // printf("hello world\n"); // Lewis
    return 0;
}
```
Running Version
