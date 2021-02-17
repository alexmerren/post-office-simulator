#include "servicePoint.h"

/* Function Definitions */
SERVICE* newServicePoint (short pointNumber) 
{
    SERVICE *newServicePoint;
    if (( newServicePoint = (SERVICE *)malloc(sizeof(SERVICE))) == NULL)
    {
        fprintf(stderr, "Ran out of memory creating service point.\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    newServicePoint->pointNumber = pointNumber;
    newServicePoint->currentCustomer = NULL;
    newServicePoint->nextServicePoint = NULL;
    return newServicePoint;
}

void addServicePoint (SERVICE** servicePoint, short pointNumber)
{
    /* This is the same adding function as customer.c */
    if (*servicePoint == NULL)
    {
        *servicePoint = newServicePoint(pointNumber);
        return;
    }

    SERVICE *currentServicePoint = *servicePoint;
    while ( currentServicePoint->nextServicePoint != NULL )
    {
        currentServicePoint = currentServicePoint->nextServicePoint;
    }
    currentServicePoint->nextServicePoint = newServicePoint(pointNumber);
}

int amountBeingServed (SERVICE* servicePoint)
{
    int amount = 0;
    SERVICE *currentService = servicePoint;
    while ( currentService != NULL )
    {
        if (currentService->currentCustomer != NULL)
        {
            amount++;
        }
        currentService = currentService->nextServicePoint;
    }
    return amount;
}

void closeServicePoints (SERVICE* servicePoint)
{
    SERVICE *tempPtr;
    while ( servicePoint != NULL )
    {
        tempPtr = servicePoint;
        servicePoint = servicePoint->nextServicePoint;
        free(tempPtr);
    }
}