//
// Created by sm1091 on 01/04/2022.
//
#include "stdlib.h"
#include "samlib.c"
#include "math.h"

typedef struct TIMENODE {
    struct TIMENODE *prevTime;
    int waitTime;
} timenode_t;

typedef struct {
    int totalCarsTransferred;

    timenode_t *tailTime;
    int overflowTime;  // Once we have completed 500 iterations, we then start the overflow counter, to count
    // how long it takes for the side to clear
} stats_t;


stats_t *createStats() {
    stats_t *stats = (stats_t *) xmalloc(sizeof(stats_t));

    stats->totalCarsTransferred = 0;
    stats->tailTime = NULL;

    stats->overflowTime = 0;
    return stats;
}

void addWaitTime(stats_t *stats, int time) {
    timenode_t *timenode = (timenode_t *) xmalloc(sizeof(timenode_t));

    timenode->waitTime = time;


    timenode->prevTime = stats->tailTime;
    stats->tailTime = timenode;
};

double avgWaitTime(stats_t *stats) {
    if (stats->totalCarsTransferred == 0) return -1;

    timenode_t *currentNode = stats->tailTime;
    int rT = 0;

//    while ((currentNode = currentNode->prevTime) != NULL) {
//        rT += currentNode->waitTime;
//    }

    for (int i = 0; i < stats->totalCarsTransferred - 1; ++i) {
        if (currentNode->waitTime > 500) continue;

        rT += currentNode->waitTime;
        if (currentNode->prevTime == NULL) continue;

        currentNode = currentNode->prevTime;
    }

    return (double) rT / stats->totalCarsTransferred;
}

int maxWaitTime(stats_t *stats) {
    timenode_t *currentNode = stats->tailTime;
    int cMax = currentNode->waitTime;

    for (int i = 0; i < stats->totalCarsTransferred; ++i) {
        if (currentNode->waitTime > 500 || currentNode->prevTime == NULL) continue;

        currentNode = currentNode->prevTime;
        if (currentNode->waitTime < 500 && currentNode->waitTime > cMax) {
            cMax = currentNode->waitTime;
        }
    }

    return cMax;
}