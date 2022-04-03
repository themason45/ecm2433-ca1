//
// Created by sm1091 on 03/04/2022.
//

#ifndef CA1_STATS_H
#define CA1_STATS_H

#include "samlib.h"


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

stats_t *createStats();
void addWaitTime(stats_t *stats, int time);
double avgWaitTime(stats_t *stats);
int maxWaitTime(stats_t *stats);

#endif //CA1_STATS_H
