#include <stdlib.h>
#include <stdio.h>
#include "emalloc.h"

//this file is made by Zastre and was given to seng 265 students for reference in the spring 2020 term


void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(1);
    }

    return p;
}
