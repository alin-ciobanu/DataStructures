#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "binaryTree.h"
#include "./../utils/utils.h"

#define NO_OF_TESTS 100
#define MAX_TREE_SIZE 250000


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
        printf("Length of the tree is not correct. Should be %d, but is %d. FAILED.\n", treeSize, treeLen);
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

    clock_t t0 = clock();

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

    clock_t t = clock();
    float time = ((float)t - (float)t0) / CLOCKS_PER_SEC;

    printf("Total: %d, Passed: %d, Execution time: %.2fs\n", loops, passedTests, time);
}


int main () {

    runTests();

    return 0;

}
