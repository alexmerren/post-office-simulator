#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer.h"

// Struct Definition
struct servicePoint
{
    short pointNumber;
    CUSTOMER* currentCustomer;
};
typedef struct servicePoint SERVICE;

// Function Prototypes
static SERVICE *newServicePoint (short);
extern void     processCustomer (SERVICE*, CUSTOMER*);