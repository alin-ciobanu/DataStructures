#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "binaryTree.h"

#define NO_OF_TESTS 100
#define MAX_TREE_SIZE 250000

#define MAX_INT 1000000

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))


static void shuffle(void *array, size_t n, size_t size) {
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


T getRandomValue () {
    return (rand() % MAX_INT * 2 + 1) - MAX_INT;
}


int runTestDuplicates (int testNo) {

    clock_t t0 = clock();

    int treeSize = (MAX_TREE_SIZE * testNo) / NO_OF_TESTS;
    if (testNo < 10) {
        treeSize = testNo; // edge cases for trees with a few elements
    }
    printf("Running DUPLICATE test %d. Tree size is %d. ", testNo, treeSize);
    Tree* tree = NULL;
    T values[treeSize];

    int i;
    for (i = 0; i < treeSize; i++) {
        T value = i;
        values[i] = value;
    }

    shuffle(values, NELEMS(values), sizeof(values[0]));

    for (i = 0; i < treeSize; i++) {
	    addT(&tree, values[i]);
    }

    shuffle(values, NELEMS(values), sizeof(values[0]));

    for (i = 0; i < treeSize; i++) {
	    addT(&tree, values[i]);
    }


    for (i = 0; i < treeSize; i++) {
        Tree* found = findT(tree, values[i]);
        if (found == NULL || found->value != values[i]) {
            printf("%d is in the tree but find function didn't find it. FAILED.\n", values[i]);
            destroyT(&tree);
            return 0;
        }
    }

    int treeLen = lengthT(tree);
    if (treeLen != treeSize) {
        printf("Length of the tree is not correct. Should be %d, but is %d. FAILED.\n", treeSize, tree);
        destroyT(&tree);
        return 0;
    }

	destroyT(&tree);
    
    clock_t t = clock();

    float time = ((float)t - (float)t0) / CLOCKS_PER_SEC;
    printf("PASSED in %.2fs. \n", time);

    return 1;

}


int runTestAddFind (int testNo) {

    clock_t t0 = clock();

    int treeSize = (MAX_TREE_SIZE * testNo) / NO_OF_TESTS;
    if (testNo < 10) {
        treeSize = testNo; // edge cases for trees with a few elements
    }
    printf("Running ADD_FIND test %d. Tree size is %d. ", testNo, treeSize);
    Tree* tree = NULL;
    T values[treeSize * 2];

    int i;
    for (i = 0; i < treeSize; i++) {
        T value = getRandomValue(); // values that are in tree
        values[i] = value;
        addT(&tree, value);
    }
    for (i = treeSize; i < treeSize * 2; i++) {
        // values that are not in the tree
        values[i] = pow(-1, i) * (MAX_INT + abs(getRandomValue()));
    }

    for (i = 0; i < treeSize * 2; i++) {
        Tree* found = findT(tree, values[i]);
        if (i < treeSize && (found == NULL || found->value != values[i])) {
            printf("%d is in the tree but find function didn't find it. FAILED.\n", values[i]);
            destroyT(&tree);
            return 0;
        }
        else if (i >= treeSize && found != NULL) {
            printf("%d is not in the tree but find function found it. FAILED.\n", values[i]);
            destroyT(&tree);
            return 0;
        }
    }

	destroyT(&tree);
    
    clock_t t = clock();

    float time = ((float)t - (float)t0) / CLOCKS_PER_SEC;
    printf("PASSED in %.2fs. \n", time);

    return 1;

}


int runTestRemove (int testNo) {

    clock_t t0 = clock();

    int treeSize = (MAX_TREE_SIZE * testNo) / NO_OF_TESTS;
    if (testNo < 10) {
        treeSize = 5; // edge cases for trees with a few elements
    }
    printf("Running REMOVE test %d. Tree size is %d. ", testNo, treeSize);
    Tree* tree = NULL;
    T values[treeSize];

    int i;
    for (i = 0; i < treeSize; i++) {
        T value = getRandomValue(); // values that are in tree
        values[i] = value;
        addT(&tree, value);
    }
    for (i = 0; i < treeSize; i++) {
        T value = values[i];
        removeT(&tree, value);
        value = getRandomValue();
        removeT(&tree, value); // should not find this value and do nothing
    }
    
    if (lengthT(tree) != 0) {
        printf("Length of the tree is not zero after removing all elements. FAILED.\n");
        destroyT(&tree);
        return 0;
    }

    destroyT(&tree);
    
    clock_t t = clock();

    float time = ((float)t - (float)t0) / CLOCKS_PER_SEC;
    printf("PASSED in %.2fs. \n", time);

    return 1;

}


void runTests () {
    int i;
    int passedTests = 0;
    int loops = 0;
    for (i = 0; i < NO_OF_TESTS; i++) {
        passedTests += runTestAddFind(i + 1);
        loops++;
    }
    printf("-----------------------------------------\n");
    for (i = 0; i < NO_OF_TESTS; i++) {
        passedTests += runTestDuplicates(i + 1);
        loops++;
    }
    printf("-----------------------------------------\n");
    for (i = 0; i < NO_OF_TESTS; i++) {
        passedTests += runTestRemove(i + 1);
        loops++;
    }
    printf("-----------------------------------------\n");

    printf("Total: %d, Passed: %d\n", loops, passedTests);
}


int main () {

    srand (time(NULL));
    runTests();

    return 0;

}
