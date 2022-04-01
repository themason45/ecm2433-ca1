//
// Created by sm1091 on 31/03/2022.
//
#include "stdlib.h"


node_t *enqueue(node_t **tail, int value) {
    node_t *newNode;
    if ((newNode = (node_t *) malloc(sizeof(node_t))) == NULL) {
//        Could not allocate memory
//        TODO: Warn the user here
    }

    newNode->nextNode = *tail;
    newNode->iterAdded = value;

//    If the tail is null, then this is the first item, so return the new node as the head
    node_t *head = NULL;
    if (*tail == NULL) {
        head = newNode;
    }

    *tail = newNode;
    return head;
}

int dequeue(node_t **head) {
    node_t *h = *head;
    node_t *newHead = h->nextNode;

    int value = h->iterAdded;
    free(h);

    *head = newHead;
    return value;
}