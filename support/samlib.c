//
// Created by sm1091 on 01/04/2022.
//

// An assortion of things that may be needed, sort of a pun of "stdlib.h"

#include "samlib.h"
#define STDEV 4.0

void *xmalloc(size_t size) {
    void *ptr = NULL;
    if ((ptr = malloc(size)) == NULL) {
//        Inform the user somehow
        fprintf(stderr, "Unable to allocate %ld bytes", size);
    }
    return ptr;
}

bool randBool(gsl_rng *r, double cutOff) {
//    This is a gaussian distribution, so the stdev value affects the standard distribution
//    https://www.gnu.org/software/gsl/doc/html/randist.html#c.gsl_ran_gaussian
    double val = gsl_ran_gaussian(r, STDEV);

//    Return true if our random number is above, or equal to 0, and we have no bias
    if (cutOff == 0) return val >= 0;

//    Return true if our random number is under our cutoff (there is a higher probability if the cutoff is
//    within 1 stdev etc), look at the PGF graph on the link above
    return fabs(val) <= cutOff;
}