#define T int

typedef struct Tree {
    T value;
    struct Tree* left;
    struct Tree* right;
    struct Tree* parent;
} Tree;

void addT (Tree** root, T value);
Tree* findMinT (Tree* root);
void removeT (Tree** root, T value);
Tree* findT (Tree* root, T value);
int lengthT (Tree* root);
void printT (Tree* root);
void destroyT (Tree** root);
