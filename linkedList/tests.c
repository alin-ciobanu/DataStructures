#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "linkedList.h"
#include "./../utils/utils.h"

#define NO_OF_TESTS 100
#define MAX_LIST_SIZE 100000


int runTestLength (int testNo) {

    clock_t t0 = clock();

    int listSize = (int) pow ( (float) (MAX_LIST_SIZE * testNo) / NO_OF_TESTS, (float) testNo / NO_OF_TESTS);

    printf("Running LENGTH test %d. List size is %d. ", testNo, listSize);
    LinkedList list;
    initL(&list);

    int i;
    for (i = 0; i < listSize; i++) {
        T value = getRandomValue();
        addL(&list, value);
    }

    int listLen = lengthL(list);
    if (listLen != listSize) {
        printf("Length of the list is not correct. It is %d, but should be %d. FAILED.\n", listLen, listSize);
        destroyL(&list);
        return 0;
    }

    destroyL(&list);
    
    clock_t t = clock();

    float time = ((float)t - (float)t0) / CLOCKS_PER_SEC;
    printf("PASSED in %.2fs. \n", time);

    return 1;

}


int runTestRemoveWithLotsOfDuplicates (int testNo) {

    clock_t t0 = clock();

    int listSize = (int) pow ( (float) (MAX_LIST_SIZE * testNo) / NO_OF_TESTS, (float) testNo / NO_OF_TESTS);

    printf("Running REMOVE_ALL test %d. List size is %d. ", testNo, listSize);
    LinkedList list;
    initL(&list);
    T *values = (T*) malloc (listSize * sizeof(T));

    T duplicatedValue = 0;

    int i;
    for (i = 0; i < listSize / 2; i++) {
        T value = getRandomValue();
        values[i] = value != 0 ? value : i + 1;
    }
    for (i = listSize / 2; i < listSize; i++) {
        values[i] = duplicatedValue;
    }

    shuffle(values, NELEMS(values), sizeof(values[0]));

    for (i = 0; i < listSize; i++) {
	    addL(&list, values[i]);
    }

    removeAllL(&list, duplicatedValue);
    int correctLength = listSize / 2;


    for (i = 0; i < listSize; i++) {
        T value = values[i];
        ListNode* found = findL(list, value);

        if (value == duplicatedValue) {
            // should not be found in the list
            if (found != NULL) {
                printf("%d should not be found in the list but find function found it. FAILED.\n", value);
                destroyL(&list);
                free(values);
                return 0;
            }
        }
        else {
            // value should be in the list
            if (found == NULL || found->value != value) {
                printf("%d should be found in the list but find function didn't find it. FAILED.\n", value);
                destroyL(&list);
                free(values);
                return 0;
            }
        }
    }

    int listLen = lengthL(list);
    if (listLen != correctLength) {
        printf("Length of the list is not correct. It is %d, but should be %d. FAILED.\n", listLen, correctLength);
        destroyL(&list);
        free(values);
        return 0;
    }

	destroyL(&list);
    free(values);
    
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
        passedTests += runTestLength(i + 1);
        loops++;
    }
    printf("-----------------------------------------\n");
    for (i = 0; i < NO_OF_TESTS; i++) {
        passedTests += runTestRemoveWithLotsOfDuplicates(i + 1);
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
