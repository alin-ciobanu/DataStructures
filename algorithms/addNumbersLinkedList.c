#include <stdio.h>
#include <stdlib.h>

#include "./../linkedList/linkedList.h"
#include "./../utils/utils.h"

// Given two numbers represented by two linked lists, write a function that returns sum list.
// The sum list is linked list representation of addition of two input numbers.
// It is not allowed to modify the lists. Also, not allowed to use explicit extra space

int add (LinkedList list1, LinkedList list2, LinkedList* sumList, int diff) {
    int sum, rest;

    if (list1 == NULL && list2 == NULL) {
        return 0;
    }

    if (diff == 0) {
        rest = add(list1->next, list2->next, sumList, diff);
        sum = list1->value + list2->value + rest;
    }
    else if (diff < 0) {
        rest = add(list1, list2->next, sumList, diff + 1);
        sum = list2->value + rest;
    }
    else {
        rest = add(list1->next, list2, sumList, diff - 1);
        sum = list1->value  + rest;
    }

    addL(sumList, sum % 10);
    return sum / 10;
}

LinkedList addNumbers (LinkedList list1, LinkedList list2) {
    int len1, len2, rest, diff;
    LinkedList sumList;

    len1 = lengthL(list1);
    len2 = lengthL(list2);

    if (len1 == 0 && len2 == 0) {
        return NULL;
    }

    initL(&sumList);
    diff = len1 - len2;
    rest = add(list1, list2, &sumList, diff);
    if (rest > 0) {
        addL(&sumList, rest);
    }
    return sumList;
}


int main () {

    LinkedList list1, list2, list3;
    initL(&list1);
    initL(&list2);
    initL(&list3);

    addL(&list1, 3);
    addL(&list1, 1);
    addL(&list1, 7);
    addL(&list1, 8);
    addL(&list1, 2);
    addL(&list1, 1);
    // list1 = 128713

    addL(&list2, 4);
    addL(&list2, 6);
    addL(&list2, 5);
    addL(&list2, 7);
    addL(&list2, 9);
    // list2 = 97564

    LinkedList sumList = addNumbers(list2, list1);
    printL(sumList);

    return 0;
}
