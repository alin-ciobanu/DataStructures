#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "binaryTree.h"

void addT(Tree** root, T value) {
    if (*root == NULL) {
        *root = (Tree*) malloc(sizeof(Tree));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    if (value < (*root)->value) {
        return addT(&((*root)->left), value);
    }
    if (value > (*root)->value) {
        return addT(&((*root)->right), value);
    }
}

Tree* findMinT (Tree* root) {
	if (root == NULL || root->left == NULL) {
		return root;
	}
	else {
		return findMinT(root->left);
	}
}

void removeT (Tree** root, T value) {
    if (*root == NULL) {
        return;
    }
    if (value < (*root)->value) {
        return removeT(&((*root)->left), value);
    }
    if (value > (*root)->value) {
        return removeT(&((*root)->right), value);
    }
    if ((*root)->right == NULL && (*root)->left == NULL) {
    	destroyT(&(*root));
        return;
    }
    if ((*root)->left != NULL && (*root)->right == NULL) {
    	Tree* temp = *root;
        *root = (*root)->left;
        free(temp);
        return;
    }
    if ((*root)->right != NULL && (*root)->left == NULL) {
    	Tree* temp = *root;
        *root = (*root)->right;
        free(temp);
        return;
    }

    Tree* min = findMinT((*root)->right);
    (*root)->value = min->value;
    removeT((&(*root)->right), (*root)->value);

}

Tree* findT (Tree* root, T value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    if (value > root->value) {
        return findT(root->right, value);
    }
    else {
        return findT(root->left, value);
    }
}

int lengthT (Tree* root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + lengthT(root->left) + lengthT(root->right);
}

void printT (Tree* root) {
    if (root == NULL) {
        return;
    }

    printT(root->left);
    printf("%d ", root->value);
    printT(root->right);

}

void destroyT (Tree** root) {
	if (*root == NULL) {
		return;
	}
	destroyT(&((*root)->left));
	destroyT(&((*root)->right));
	free(*root);
	*root = NULL;
}
