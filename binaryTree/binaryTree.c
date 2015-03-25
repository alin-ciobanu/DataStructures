#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define T int
#define NO_OF_TESTS 500
#define MAX_TREE_SIZE 250000

#define MAX_INT 1000000

typedef struct Tree {
    T value;
    struct Tree* left;
    struct Tree* right;
} Tree;

void addT(Tree** root, T value) {
    if (*root == NULL) {
        *root = (Tree*) malloc(sizeof(Tree));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    if (value < (*root)->value) {
        addT(&((*root)->left), value);
    }
    if (value > (*root)->value) {
        addT(&((*root)->right), value);
    }
}

void removeT(Tree** root, T value) {
    if (*root == NULL) {
        return;
    }
    if (value < (*root)->value) {
        return removeT(&((*root)->left), value);
    }
    if (value > (*root)->value) {
        return removeT(&((*root)->left), value);
    }
    if ((*root)->right == NULL && (*root)->left == NULL) {
        free(*root);
        *root = NULL;
        return;
    }
    if ((*root)->left != NULL && (*root)->right == NULL) {
        free(*root);
        *root = (*root)->left;
        return;
    }
    if ((*root)->right != NULL && (*root)->left == NULL) {
        free(*root);
        *root = (*root)->right;
        return;
    }

    (*root)->value = ((*root)->left)->value;
    removeT(&((*root)->left), (*root)->value);

}

Tree* findT (Tree* root, T value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    if (value > root->value) {
        return findT(root->right, value);
    }
    if (value < root->value) {
        return findT(root->left, value);
    }
}

void printT (Tree* root) {
    if (root == NULL) {
        return;
    }

    printT(root->left);
    printf("%d ", root->value);
    printT(root->right);

}

T getRandomValue () {
    return (rand() % MAX_INT * 2 + 1) - MAX_INT;
}

int runTest (int testNo) {

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
            return 0;
        }
        else if (i >= treeSize && found != NULL) {
            printf("%d is not in the tree but find function found it. FAILED.\n", values[i]);
            return 0;
        }
    }

    clock_t t = clock();
    float time = (((float)t - (float)t0) / 1000000.0F ) * 1000;

    printf("PASSED in %.3fs. \n", time);
    return 1;

}

void runTests () {
    int i;
    int passedTests = 0;
    for (i = 0; i < NO_OF_TESTS; i++) {
        passedTests += runTest(i + 1);
    }
    printf("-----------------------------------------\nTotal: %d, Passed: %d\n", NO_OF_TESTS, passedTests);
}


int main () {

    srand (time(NULL));
    runTests();

    return 0;

}
