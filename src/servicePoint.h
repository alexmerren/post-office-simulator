#include <stdlib.h>
#include <stdio.h>
#include "customer.h"
#ifndef __SERVICEPOINT_H
#define __SERVICEPOINT_H 1

/* Struct Definition */
struct servicePoint
{
    short pointNumber;
    CUSTOMER *currentCustomer;
    struct servicePoint *nextServicePoint;
};
typedef struct servicePoint SERVICE;

/* Function Prototypes */
static SERVICE* newServicePoint     (short);
extern void     addServicePoint     (SERVICE**, short);
extern int      amountBeingServed   (SERVICE*);
extern void     closeServicePoints  (SERVICE*);

#endif