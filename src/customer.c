#include "customer.h"

/* Function Definitions */
static CUSTOMER* newCustomer (short waitingTime, short processTime)
{
    CUSTOMER *newCustomer;
    if (( newCustomer = (CUSTOMER *)malloc(sizeof(CUSTOMER))) == NULL)
    {
        fprintf(stderr, "Memory allocation error for customer.\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    newCustomer->waitingTime = waitingTime; 
    newCustomer->processTime = processTime;
    newCustomer->nextCustomer = NULL;
    return newCustomer;
}


extern void addToQueue(CUSTOMER** queue, unsigned short waitingSeed, unsigned short processSeed)
{
    /* If the queue is empty, just add to the queue without
    checking the next customer status. */
    if (*queue == NULL)
    {
        *queue = newCustomer(waitingSeed, processSeed);
        return;
    }

    /* If the queue is not empty, then loop through until we get to the end. */
    CUSTOMER *currentCustomer = *queue;
    while ( currentCustomer->nextCustomer != NULL )
    {
        currentCustomer = currentCustomer->nextCustomer;
    }
    currentCustomer->nextCustomer = newCustomer(waitingSeed, processSeed);
}

extern CUSTOMER* removeFromQueue (CUSTOMER** queue, CUSTOMER* customerToRemove)
{
    CUSTOMER *currentCustomer = *queue;
    CUSTOMER *previousCustomer = NULL;
    CUSTOMER *tempPtr = NULL;

    /* Loop through the queue until we reach the end. */
    while ( currentCustomer != NULL )
    {
        /* If no customer is specified, it removes the first in the queue. */
        if ( customerToRemove == NULL )
        {
            tempPtr = currentCustomer;
            *queue = currentCustomer->nextCustomer;
            return tempPtr;
        }

        /* If a customer to remove is specified, then remove that customer. */
        if ( currentCustomer == customerToRemove )
        {
            /* If the specified customer is the first in the queue, 
            recall the function with customerToRemove == NULL. */
            if ( previousCustomer == NULL )
            {
                tempPtr = removeFromQueue(queue, NULL);
                return tempPtr;
            }

            /* If the customerToRemove is at any other point in the queue,
            make the previous customer's next customer as the current customer's
            next customer. TODO I am aware this is not great wording. */
            previousCustomer = currentCustomer;
            tempPtr = currentCustomer;
            previousCustomer->nextCustomer = currentCustomer->nextCustomer;
            return tempPtr;
        }

        /* Iterate through the queue. */
        tempPtr = currentCustomer;
        currentCustomer = currentCustomer->nextCustomer;
    }

    /* If the queue is empty, return NULL as nothing is removed. */
    return NULL;
}

extern void leavePostOffice (CUSTOMER* customer)
{
    free(customer);
}

extern int incrementCounter (CUSTOMER* customer)
{
    return ++customer->counter;
}

extern int sizeOfQueue (CUSTOMER* customer)
{
    int counter = 0;
    while ( customer != NULL )
    {
       counter++;
       customer = customer->nextCustomer;
    }
    return counter;
}

extern void printQueue (CUSTOMER* customer)
{
    int currentCounter, waitingTime, processTime;
    while ( customer != NULL )
    {
        waitingTime = customer->waitingTime;
        currentCounter = customer->counter;
        processTime = customer->processTime;
        printf("Customer has waiting tolerance %u, process tolerance %u, and has been waiting for %d.\n",
                waitingTime, processTime,  currentCounter);
        customer = customer->nextCustomer;
    }
}

extern void clearQueue (CUSTOMER* customer)
{
    CUSTOMER *tempPtr;
    while ( customer != NULL ) 
    {
        tempPtr = customer;
        customer = customer->nextCustomer;
        free(tempPtr);
    }
}