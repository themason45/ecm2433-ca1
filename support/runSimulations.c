//
// Created by sm1091 on 03/04/2022.
//

#include "sim.h"
#include "time.h"

int main(int argc, char **argv) {
//  Set up the random stuff
    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    double lARate = 4.0;
    double rARate = 4.0;

    int lGPer = 6;
    int rGPer = 6;

    printf("Parameter values: \n" \
           "\tFrom left: \n" \
           "\t\t traffic arrival rate : %f \n" \
           "\t\t traffic light period: %d \n" \
           "\tFrom right: \n" \
           "\t\t traffic arrival rate : %f \n" \
           "\t\t traffic light period: %d \n", lARate, lGPer, rARate, rGPer);

    run100Simulations(r, lGPer, rGPer, lARate, rARate);

    return EXIT_SUCCESS;
}