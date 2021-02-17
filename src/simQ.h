#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gsl/gsl_rng.h"
#include "servicePoint.h"
#include "customer.h"
#ifndef __SIMQ_H
#define __SIMQ_H 1

/* Function Prototypes */
extern int              getParamValue       (char*, char[]);
extern void             createOutputFile    (char*);
extern void             checkParams         (int);

#endif