#include "stdlib.h"
#include "stdbool.h"
#include "time.h"
#include "gsl/gsl_rng.h"
#include "support/side.c"

// How many iterations are we going to run?
#define ITER_COUNT 100

// Store the simulation info in a struct, so we can pass this back to the
typedef struct {
    side_t *left;
    side_t *right;

    gsl_rng *randRange;
} sim_t;

void runOneSimulation(sim_t *sim) {
    gsl_rng *r = sim->randRange;
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

//    while (lCarCount > 0 || rCarCount > 0) {
////         Choose either option
//
////         If we're choosing not to change the lights, then don't add any more cars
//    }
//  Once all iterations are complete, we have to clear both ends, with further iterations
}

sim_t *createSimulation(gsl_rng *r, int leftGreenTime, int rightGreenTime) {
    sim_t *sim = (sim_t *) xmalloc(sizeof(sim_t));

    sim->randRange = r;

    bool leftStartsGreen = randBool(r, 4);
    sim->left = createSide(r, leftStartsGreen, leftGreenTime);
    sim->right = createSide(r, !leftStartsGreen, rightGreenTime);

    return sim;
}

int main() {
//  Set up the random stuff
    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    sim_t *simulation = createSimulation(r, 6, 6);
    runOneSimulation(simulation);

    return EXIT_SUCCESS;
}