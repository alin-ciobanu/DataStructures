#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

ListNode* createNewNode (T value, ListNode* nextNode) {
	ListNode* newNode = (ListNode*) malloc (sizeof (ListNode));
	newNode->value = value;
	newNode->next = nextNode;
	return newNode;
}

void initL(LinkedList* list) {
	*list = NULL;
}

ListNode* findL (LinkedList list, T value) {
	while (list != NULL) {
		if (list->value == value) {
			return list;
		}
		list = list->next;
	}
	return NULL;
}

void addL (LinkedList* list, T value) {
	ListNode* oldHead = *list;
	*list = createNewNode(value, oldHead);
}

void removeL (LinkedList* list, T value) {
	if (*list == NULL) {
		return; // node with value doesn't exist
	}
	if ((*list)->value == value) {
		ListNode* temp = *list;
		*list = (*list)->next;
		free(temp);
		return;
	}

	ListNode* iterator = *list;

	while (iterator->next != NULL) {
		if (iterator->next->value == value) {
			ListNode* temp = iterator->next;
			iterator->next = iterator->next->next;
			free(temp);
			return;
		}
		iterator = iterator->next;
	}
}

void removeAllL (LinkedList* list, T value) {
	if (*list == NULL) {
		return; // node with value doesn't exist
	}
	if ((*list)->value == value) {
		ListNode* temp = *list;
		*list = (*list)->next;
		free(temp);
		return removeAllL(&(*list), value);
	}

	ListNode* iterator = *list;

	while (iterator->next != NULL) {
		if (iterator->next->value == value) {
			ListNode* temp = iterator->next;
			iterator->next = iterator->next->next;
			free(temp);
		}
		else {
			iterator = iterator->next;
		}
	}
}

int lengthL (LinkedList list) {
	int size = 0;
	while (list != NULL) {
		size++;
		list = list->next;
	}
	return size;
}

void destroyL (LinkedList* list) {
	if (*list == NULL) {
		return;
	}
	destroyL(&((*list)->next));
	free(*list);
	*list = NULL;
}

void printL (LinkedList list) {
	while (list != NULL) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}
