//
// Created by sm1091 on 01/04/2022.
//

#include "stdlib.h"
#include "stdbool.h"
#include "gsl/gsl_rng.h"
#include "samlib.c"

typedef struct NODE {
    struct NODE *nextNode;
    struct NODE *prevNode;

    int iterAdded;  // Iteration in which this node was created
} node_t;

typedef struct {
    node_t *head;  // The head of our queue
    node_t *tail;  // The tail of our queue

    bool hasGreenLight;  // Does this side have the green light
    gsl_rng *randRange;  // The gsl range item to base our random numbers off of (can change for different sides?)

    int currentIteration;
} side_t;

bool perhapsAddCar(side_t *side) {
//    if (!randBool(side->randRange, 4.0)) return false;

// Enqueue a car
//  Get the head of the list
//  Create a new node
    node_t *newNode = xmalloc(sizeof(node_t));

    newNode->iterAdded = side->currentIteration;
    newNode->prevNode = side->tail;

    if (newNode->prevNode != NULL) newNode->prevNode->nextNode = newNode;

//  Set the head to the new node if it is not already set (i.e: first item)
    if (side->head == NULL) side->head = newNode;

    side->tail = newNode;

//    Do statistics stuff here

    return true;  // A new car was added
}

bool perhapsTransferCar(side_t *side) {
//    If we don't have a green light, save some processing, and exit here
    if (!side->hasGreenLight) return false;

//    If we do, then check if we should (random number check), and carry on
    //    if (!randBool(side->randRange, 4.0)) return false;

    node_t *cHead = side->head;
    side->head = cHead->nextNode;
    side->head->prevNode = NULL;

    free(cHead);

//    Do statistics stuff here

    return true;
}