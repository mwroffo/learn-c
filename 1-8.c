#include <stdio.h>

main()
{
    int c, nl, t, sp;
    nl = 0;
    t = 0;
    sp = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n') ++nl;
        if (c == '\t') ++t;
        if (c == ' ') ++sp;
    }
    printf("%10s: %d\n%10s: %d\n%10s: %d\n",
            "newlines", nl,
            "tabs", t,
            "spaces",sp);
}
