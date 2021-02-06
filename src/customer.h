#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Struct Definition */
struct node 
{
    unsigned int tolerance;
    char status[12];
    struct node *nextCustomer;
};
typedef struct node CUSTOMER;

/* Function Prototypes */
static CUSTOMER *newCustomer    (unsigned int);
extern void     push            (CUSTOMER**, unsigned int);
extern void     pop             (CUSTOMER**);
extern void     printQueue      (CUSTOMER*);
