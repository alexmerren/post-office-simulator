#include "service.h"

/* Function Definitions */
SERVICE *newServicePoint (short pointNumber) 
{
    SERVICE *newServicePoint;
    if (( newServicePoint = (SERVICE *)malloc(sizeof(SERVICE))) == NULL)
    {
        fprintf(stderr, "Ran out of memory creating service point\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    newServicePoint->pointNumber = pointNumber;
    newServicePoint->currentCustomer = NULL;
    return newServicePoint;
}

void processCustomer (SERVICE *servicePoint, CUSTOMER *customer) 
{

}
