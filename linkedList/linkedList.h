#define T int


typedef struct ListNode {
	T value;
	struct ListNode* next;
} ListNode;

typedef ListNode* LinkedList;


ListNode* createNewNode (T, ListNode*);

void initL(LinkedList* list);

ListNode* findL (LinkedList list, T value);

void addL (LinkedList* list, T value);

/**
*	Deletes the first occurrence of @value from the list.
*/
void removeL (LinkedList* list, T value);

/**
*	Deletes all occurences of @value from the list.
*/
void removeAllL (LinkedList* list, T value);

int lengthL (LinkedList list);

void destroyL (LinkedList* list);

void printL (LinkedList list);
