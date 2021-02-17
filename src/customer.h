#include <stdlib.h>
#include <stdio.h>
#ifndef __CUSTOMER_H
#define __CUSTOMER_H 1

/* Struct Definition */
struct node 
{
    unsigned int waitingTime;
    unsigned int processTime;
    unsigned int counter;
    struct node *nextCustomer;
};
typedef struct node CUSTOMER;

/* Function Prototypes */
static CUSTOMER*    newCustomer         (short, short);
extern void         addToQueue          (CUSTOMER**, unsigned short, unsigned short);
extern CUSTOMER*    removeFromQueue     (CUSTOMER**, CUSTOMER*);
extern void         leavePostOffice     (CUSTOMER*);
extern int          incrementCounter    (CUSTOMER*);
extern int          sizeOfQueue         (CUSTOMER*);
extern void         printQueue          (CUSTOMER*);
extern void         clearQueue          (CUSTOMER*);

#endif