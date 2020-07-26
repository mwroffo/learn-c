#include <stdio.h>

int binsearch(int, int[], int);
int elsebinsearch(int, int[], int);

int main() {
    int actual, elseactual, expected, needle, n;

    int haystack[] = {1, 3, 9, 14, 25, 39, 41};
    n = sizeof(haystack);
     
    expected = 3;
    needle = haystack[expected];

    actual = binsearch(needle, haystack, n);
    elseactual = elsebinsearch(needle, haystack, n);

    printf("%10s: %d\n%10s: %d\n%10s: %d\n",
            "expected", expected, "actual", actual,
            "elseactual", elseactual);

    return 0;
}

/* one-comparison binary search */
int binsearch(int needle, int haystack[], int n) {
    int low, mid, high;

    low = 0;
    high = n-1;

    while (low < high) {
        mid = (low + high) / 2;
        if (needle < haystack[mid])
            high = mid - 1;
        else
            low = mid;
    } // where low==high
    return (needle == haystack[low]) ? low : -1;
}
/* two-comparison binary search */
int elsebinsearch(int needle, int haystack[], int n) {
    int low, mid, high;

     low = 0;
     high = n - 1;

     while (low <= high) {
         mid = (low + high) / 2;
         if (needle < haystack[mid])
             high = mid - 1;
         else if (needle > haystack[mid])
             low = mid + 1;
         else
             return mid; // found it
     }
     return -1;
}
