//
// Created by sm1091 on 03/04/2022.
//

#ifndef CA1_SAMLIB_H
#define CA1_SAMLIB_H

#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "stdbool.h"
#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"

void *xmalloc(size_t size);

bool randBool(gsl_rng *r, double cutOff);

#endif //CA1_SAMLIB_H
