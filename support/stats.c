//
// Created by sm1091 on 01/04/2022.
//
#include "stats.h"

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

void clearWaitTimes(stats_t*stats) {
    timenode_t *nextTime = stats->tailTime;

    while (nextTime != NULL) {
        timenode_t *ttFree = nextTime;
        nextTime = nextTime->prevTime;

        free(ttFree);
    }
}

double avgWaitTime(stats_t *stats) {
    if (stats->totalCarsTransferred == 0) return -1;

    timenode_t *currentNode = stats->tailTime;
    int rT = 0;

//    while ((currentNode = currentNode->prevTime) != NULL) {
//        rT += currentNode->waitTime;
//    }

    for (int i = 0; i < stats->totalCarsTransferred - 1; ++i) {
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
        if (currentNode->prevTime == NULL) continue;

        currentNode = currentNode->prevTime;
        if (currentNode->waitTime < 500 && currentNode->waitTime > cMax) {
            cMax = currentNode->waitTime;
        }
    }

    return cMax;
}