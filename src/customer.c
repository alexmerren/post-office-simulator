#include "customer.h"

/* Function Definitions */
static CUSTOMER *newCustomer (unsigned int tolerance)
{
    CUSTOMER *newCustomer;
    if (( newCustomer = (CUSTOMER *)malloc(sizeof(CUSTOMER))) == NULL)
    {
        fprintf(stderr, "Ran out of memory creating customer.\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    strcpy(newCustomer->status, "Waiting");
    newCustomer->tolerance = tolerance;
    newCustomer->nextCustomer = NULL;
    return newCustomer;
}

extern void push (CUSTOMER **queue, unsigned int tolerance)
{
    CUSTOMER *currentCustomer = *queue;
    CUSTOMER *nextCustomer = newCustomer(tolerance);
    if (*queue == NULL)
    {
        *queue = nextCustomer;
        return;
    }
    while (currentCustomer->nextCustomer != NULL)
    {
        currentCustomer = currentCustomer->nextCustomer;
    }
    currentCustomer->nextCustomer = nextCustomer;
}

extern void pop (CUSTOMER **queue)
{
    CUSTOMER *tempPtr = *queue;
    if (tempPtr != NULL)
    {
        *queue = tempPtr->nextCustomer;
        free(tempPtr);
    }
}

extern void printQueue (CUSTOMER *queue)
{
    CUSTOMER* currentCustomer = queue;
    while (currentCustomer != NULL)
    {
        printf("Customer has tolerance: %u\n", currentCustomer->tolerance);
        currentCustomer = currentCustomer->nextCustomer;
    }
}