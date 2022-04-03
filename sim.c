#include "stdlib.h"
#include "stdbool.h"
#include "time.h"
#include "gsl/gsl_rng.h"
#include "support/side.c"
#include "pthread.h"

// How many iterations are we going to run?
#define ITER_COUNT 500
#define SIM_COUNT 100

#define FMT_AVG(runningTotal) roundf(((double) runningTotal / SIM_COUNT) * 10) / 10

// Store the simulation info in a struct, so we can pass this back to the
typedef struct {
    side_t *left;
    side_t *right;

    gsl_rng *randRange;
} sim_t;

void runOneSimulation(sim_t *sim) {
    side_t *left = sim->left;
    side_t *right = sim->right;

    int greenItersRemaining = 0;
    int i = 0;
//  In each iteration, we could either change the lights, or run all three instructions
    for (; i < ITER_COUNT; ++i) {
//        Choose either option
        if (greenItersRemaining == 0) {
//          If true, we need to swap the lights round
            side_t *newGreen = swapSides(left, right);
//          Then set the countdown to the green length, in order to keep it green for the required length of time
            greenItersRemaining = newGreen->greenLength;
        } else {
//          If false, then we run the left, and right, add car process
            perhapsAddCar(left);
            perhapsAddCar(right);

//          Then we try transferring the cars (only one will run, depending on who has the green light)
            perhapsTransferCar(left);
            perhapsTransferCar(right);
        }

        left->currentIteration++;
        right->currentIteration++;
        greenItersRemaining--;
    }

    //  Once all iterations are complete, we have to clear both ends, with further iterations
    while (left->head != NULL || right->head != NULL) {
//         Choose either option
        if (greenItersRemaining == 0) {
//          If true, we need to swap the lights round
            side_t *newGreen = swapSides(left, right);
//          Then set the countdown to the green length, in order to keep it green for the required length of time
            greenItersRemaining = newGreen->greenLength;
        } else {
            perhapsTransferCar(left);
            perhapsTransferCar(right);
        }

        left->currentIteration++;
        right->currentIteration++;

        left->stats->overflowTime++;
        right->stats->overflowTime++;

        greenItersRemaining--;
    }

}

sim_t *createSimulation(gsl_rng *r, int leftGreenTime, int rightGreenTime, double leftRandBias, double rightRandBias) {
    sim_t *sim = (sim_t *) xmalloc(sizeof(sim_t));

    sim->randRange = r;

    bool leftStartsGreen = randBool(r, 0);
    sim->left = createSide(r, leftStartsGreen, leftGreenTime, leftRandBias);
    sim->right = createSide(r, !leftStartsGreen, rightGreenTime, rightRandBias);

    return sim;
}

void run100Simulations(gsl_rng *r, int leftGreenTime, int rightGreenTime) {
    sim_t *sims[100];

//    Initialise statistics variables
    int leftCarsPassedRunningTotal = 0;
    int rightCarsPassedRunningTotal = 0;

    double leftAvgTimeRunningTotal = 0;
    double rightAvgTimeRunningTotal = 0;

    int leftMaxRunningTotal = 0;
    int rightMaxRunningTotal = 0;

    int leftOverflowTmeRunningTotal = 0;
    int rightOverflowTmeRunningTotal = 0;

    for (int i = 0; i < SIM_COUNT; ++i) {
//      Create a simulation
//        printf("Simulation %d\n", i);
        sim_t *sim = sims[i] = createSimulation(r, leftGreenTime, rightGreenTime);

//        printf("Running\n");
        runOneSimulation(sim);

//        printf("Done\n");
//        Update the current stats
        stats_t *lStats = sim->left->stats;
        stats_t *rStats = sim->right->stats;

        leftCarsPassedRunningTotal += lStats->totalCarsTransferred;
        rightCarsPassedRunningTotal += rStats->totalCarsTransferred;

//        printf("Calculating averages\n");
//        printf("%f\n", avgWaitTime(lStats));
        leftAvgTimeRunningTotal += avgWaitTime(lStats);
        rightAvgTimeRunningTotal += avgWaitTime(rStats);

//        printf("Calculating wait time averages\n");
        leftMaxRunningTotal += maxWaitTime(lStats);
        rightMaxRunningTotal += maxWaitTime(rStats);

        leftOverflowTmeRunningTotal += lStats->overflowTime;
        rightOverflowTmeRunningTotal += rStats->overflowTime;
    }

//    Clear up here
    for (int i = 0; i < SIM_COUNT; ++i) {
        free(sims[i]);
    }

//    Display full results
    printf("Results (averaged over 100 runs): \n"
           "\tFrom left: \n"
           "\t\t number of vehicles: %.2f\n"
           "\t\t average waiting time: %.2f\n"
           "\t\t maximum waiting time: %.2f\n"
           "\t\t clearance time: %.2f\n"
           "\tFrom right: \n"
           "\t\t number of vehicles: %.2f\n"
           "\t\t average waiting time: %.2f\n"
           "\t\t maximum waiting time: %.2f\n"
           "\t\t clearance time: %.2f\n",
           FMT_AVG(leftCarsPassedRunningTotal),
           FMT_AVG(leftAvgTimeRunningTotal),
           FMT_AVG(leftMaxRunningTotal),
           FMT_AVG(leftOverflowTmeRunningTotal),
           FMT_AVG(rightCarsPassedRunningTotal),
           FMT_AVG(rightAvgTimeRunningTotal),
           FMT_AVG(rightMaxRunningTotal),
           FMT_AVG(rightOverflowTmeRunningTotal)
    );
}

int main() {
//  Set up the random stuff
    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    int lARate = 0;
    int rARate = 0;

    int lGPer = 6;
    int rGPer = 6;

    printf("Parameter values: \n" \
           "\tFrom left: \n" \
           "\t\t traffic arrival rate : %d \n" \
           "\t\t traffic light period: %d \n" \
           "\tFrom right: \n" \
           "\t\t traffic arrival rate : %d \n" \
           "\t\t traffic light period: %d \n", lARate, lGPer, rARate, rGPer);

    run100Simulations(r, 3, 3);

//    TODO: Add a car arrival rate adjuster


    return EXIT_SUCCESS;
}