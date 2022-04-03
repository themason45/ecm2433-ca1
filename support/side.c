//
// Created by sm1091 on 01/04/2022.
//
#include "side.h"

void clearSide(side_t* side) {
    if (side->head != NULL) free(side->head);
    if (side->tail != NULL) free(side->tail);

    clearWaitTimes(side->stats);
}

side_t *createSide(gsl_rng *r, bool hasGreenLight, int greenLength, double randBias) {
    side_t *side = (side_t *) xmalloc(sizeof(side_t));

    side->tail = NULL;
    side->head = NULL;

    side->currentIteration = 0;
    side->randRange = r;
    side->hasGreenLight = hasGreenLight;

    side->greenLength = greenLength;
    side->randBias = randBias;

    side->stats = createStats();
    return side;
}

bool perhapsAddCar(side_t *side) {
//    The randBias is only used for adding cars, not removing them
    if (!randBool(side->randRange, side->randBias)) return false;

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

    return true;  // A new car was added
}

bool perhapsTransferCar(side_t *side) {
//    If we don't have a green light, save some processing, and exit here
    if (!side->hasGreenLight) return false;

//    If we do, then check if we should (random number check), and carry on
    if (!randBool(side->randRange, 0)) return false;

    node_t *cHead = side->head;
    if (cHead == NULL) return false;  // There are no cars to transfer, so return false

//    Do statistics stuff here
    int waitTime = side->currentIteration - cHead->iterAdded;
    addWaitTime(side->stats, waitTime);
    side->stats->totalCarsTransferred++;

//  Now remove this item, and replace it with the next item
    side->head = cHead->nextNode;

    if (side->head != NULL) side->head->prevNode = NULL;

    free(cHead);

    return true;
}

side_t *swapSides(side_t *s1, side_t *s2) {
    bool s1Green = s1->hasGreenLight;

    s1->hasGreenLight = !s1Green;
    s2->hasGreenLight = s1Green;

//    If side 1 wasn't green to begin with, it will be now, so return it
    if (!s1Green) return s1;
//    Otherwise, return side 2
    return s2;
}