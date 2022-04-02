//
// Created by sm1091 on 01/04/2022.
//

// An assortion of things that may be needed, sort of a pun of "stdlib.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"

void *xmalloc(size_t size) {
    void *ptr = NULL;
    if ((ptr = malloc(size)) == NULL) {
//        Inform the user somehow
        fprintf(stderr, "Unable to allocate %ld bytes", size);
    }
    return ptr;
}

bool randBool(gsl_rng *r, double stdev) {
//    This is a gaussian distribution, so the stdev value affects the standard distribution
//    https://www.gnu.org/software/gsl/doc/html/randist.html#c.gsl_ran_gaussian
    double val = gsl_ran_gaussian(r, stdev);

//    Return true if our random number is above, or equal to 0
    return val >= 0;
}