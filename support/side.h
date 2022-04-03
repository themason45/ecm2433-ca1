//
// Created by sm1091 on 03/04/2022.
//

#ifndef CA1_SIDE_H
#define CA1_SIDE_H

#include "stats.h"

typedef struct NODE {
    struct NODE *nextNode;
    struct NODE *prevNode;

    int iterAdded;  // Iteration in which this node was created
} node_t;

typedef struct {
    node_t *head;  // The head of our queue
    node_t *tail;  // The tail of our queue

    bool hasGreenLight;  // Does this side have the green light
    int greenLength;
    double randBias;
    gsl_rng *randRange;  // The gsl range item to base our random numbers off of (can change for different sides?)

    int currentIteration;

    stats_t *stats;
} side_t;

side_t *createSide(gsl_rng *r, bool hasGreenLight, int greenLength, double randBias);

bool perhapsAddCar(side_t *side);
bool perhapsTransferCar(side_t *side);
side_t *swapSides(side_t *s1, side_t *s2);

#endif //CA1_SIDE_H
