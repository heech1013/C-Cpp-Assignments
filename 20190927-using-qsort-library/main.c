/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *w[] = {
    "Write",
    "a",
    "test"
};

#define NWORDS (sizeof(w) / sizeof(w[0]))

int compar(const void* a, const void* b) {
    return (strcmp(*(char**)b, *(char**)a));
}

int main() {
    qsort(w, NWORDS, sizeof(w[0]), compar);
    for (int i = 0; i < NWORDS; i++) {
        printf("%s ", w[i]);
    }
}

