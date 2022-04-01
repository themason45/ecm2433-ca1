#include "stdlib.h"
#include "stdbool.h"
#include "time.h"
#include "gsl/gsl_rng.h"
#include "support/side.c"

// How many iterations are we going to run?
#define ITER_COUNT 500


void runOneSimulation(gsl_rng *r) {
//  We want to initialise our variables here
//  This includes what state our lights our in, and how many cars are on either side.
    bool lGreen = false;  // Our left light is green? If not, then our right one is
    int lCarCount = 0;
    int rCarCount = 0;
//  In each iteration, we could either change the lights, or run all three instructions
    for (int i = 0; i < ITER_COUNT; ++i) {
//        Choose either option
    }

//    while (lCarCount > 0 || rCarCount > 0) {
////         Choose either option
//
////         If we're choosing not to change the lights, then don't add any more cars
//    }
//  Once all iterations are complete, we have to clear both ends, with further iterations
}

int main() {
//  Set up the random stuff
    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r,time(0));

    runOneSimulation(r);

    side_t* left = (side_t*) xmalloc(sizeof(side_t));
    left->tail = NULL;
    left->head = NULL;

    left->currentIteration = 0;
    left->randRange = r;
    left->hasGreenLight = true;

    perhapsAddCar(left);
    left->currentIteration++;
    perhapsAddCar(left);
    left->currentIteration++;
    perhapsAddCar(left);
    left->currentIteration++;
    perhapsTransferCar(left);
    left->currentIteration++;
    perhapsAddCar(left);
    left->currentIteration++;
    perhapsTransferCar(left);

//    printf("%f", fabs(gsl_ran_gaussian(r, 4.0)));
    return EXIT_SUCCESS;
}