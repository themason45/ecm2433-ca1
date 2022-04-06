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
    if (argc != 5) {
        printf("4 arguments required. These are\n"
               "\t- Left arrival rate\n"
               "\t- Left green time\n"
               "\t- Right arrival rate\n"
               "\t- Right green time\n");
        return EXIT_FAILURE;
    }

    double lARate = atof(argv[1]);
    int lGPer = atoi(argv[2]);

    double rARate = atof(argv[3]);
    int rGPer = atoi(argv[4]);

    run100Simulations(r, lGPer, rGPer, lARate, rARate);

    return EXIT_SUCCESS;
}