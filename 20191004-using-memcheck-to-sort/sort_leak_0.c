#include <stdlib.h>
#include <stdio.h>
#include "memcheck.h"

void sort(void *v[], int n, int (*compare)(void *, void *))
{
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (compare(v[i], v[j]) > 0) {
                void *swap = v[i];
                v[i] = v[j];
                v[j] = swap;
            }
        }
    }
}

int intcmp(void *datap1, void *datap2) {
    return *(int *)datap1 - *(int *)datap2;
}

int *pi(int n) {
    int *intp = (int *)malloc(sizeof(int));
    *intp = n;
    return intp;
}

int main(void) {
    int *w[] = {pi(7), pi(1), pi(-2), pi(10)};
    const int N_ITEMS = sizeof(w) / sizeof(w[0]);
    sort((void **)w, N_ITEMS, (int (*)(void *,void *))intcmp);
    for (int i = 0; i < N_ITEMS; i++)
        printf("%d\n", *w[i]);
    for (int j = 0; j < N_ITEMS; j++)
        free(w[j]);
    print_memory_leaks();
}
