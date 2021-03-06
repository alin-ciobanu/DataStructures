#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.h"

void shuffle(void *array, size_t n, size_t size) {
    srand (time(NULL));
    char tmp[size];
    char *arr = array;
    size_t stride = size * sizeof(char);

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; ++i) {
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}

int getRandomValue () {
    srand (time(NULL));
    return (rand() % MAX_INT * 2 + 1) - MAX_INT;
}

int max (int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
