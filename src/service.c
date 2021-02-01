#include "service.h"

// Function Definitions
SERVICE *newServicePoint (short pointNumber) 
{
    SERVICE *newServicePoint;
    if (( newServicePoint = (SERVICE *)malloc(sizeof(SERVICE))) == NULL)
    {
        printf("Not enough memory when creating service point.\n");
        exit(-1);
    }
    newServicePoint->pointNumber = pointNumber;
    newServicePoint->currentCustomer = NULL;
    return newServicePoint;
}

void processCustomer (SERVICE *servicePoint, CUSTOMER *customer) 
{

}
