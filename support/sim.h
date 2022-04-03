//
// Created by sm1091 on 03/04/2022.
//

#ifndef CA1_SIM_H
#define CA1_SIM_H

#include "side.h"

// Store the simulation info in a struct, so we can pass this back to the
typedef struct {
    side_t *left;
    side_t *right;

    gsl_rng *randRange;
} sim_t;

void runOneSimulation(sim_t *sim);
sim_t *createSimulation(gsl_rng *r, int leftGreenTime, int rightGreenTime, double leftRandBias, double rightRandBias);
void run100Simulations(gsl_rng *r, int leftGreenTime, int rightGreenTime, double leftRandBias, double rightRandBias);

#endif //CA1_SIM_H
