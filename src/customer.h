#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node 
{
    unsigned int tolerance;
    char status[12];
    struct node *nextCustomer;
};
typedef struct node CUSTOMER;

static CUSTOMER *newCustomer ();
extern void     push        (CUSTOMER**);
extern void     pop         (CUSTOMER**);
extern void     printQueue  (CUSTOMER*);
extern void     emptyQueue  (CUSTOMER**);
