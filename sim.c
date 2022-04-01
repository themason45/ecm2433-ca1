#include "stdlib.h"
#include "stdbool.h"
#include "time.h"
#include "gsl/gsl_rng.h"
#include "support/side.c"

// How many iterations are we going to run?
#define ITER_COUNT 100


void runOneSimulation(gsl_rng *r) {
    bool leftStartsGreen = randBool(r, 4);
    side_t *left = createSide(r, leftStartsGreen);
    side_t *right = createSide(r, !leftStartsGreen);

//  In each iteration, we could either change the lights, or run all three instructions
    for (int i = 0; i < ITER_COUNT; ++i) {
//        Choose either option
        if (randBool(r, 4)) {
//            If true, we need to swap the lights round
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
    }

    printf("%f", avgWaitTIme(left->stats));

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

    gsl_rng_set(r, time(0));

    runOneSimulation(r);

//    printf("%f", fabs(gsl_ran_gaussian(r, 4.0)));
    return EXIT_SUCCESS;
}