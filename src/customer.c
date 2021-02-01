#include "customer.h"

// Function Definitions
static CUSTOMER *newCustomer ()
{
    CUSTOMER *newCustomer;
    if (( newCustomer = (CUSTOMER *)malloc(sizeof(CUSTOMER))) == NULL)
    {
        printf("Not enough memory!\n");
        exit(-1);
    }
    newCustomer->nextCustomer = NULL;
    strcpy(newCustomer->status, "Waiting");
    return newCustomer;
}

extern void push (CUSTOMER **head)
{
    CUSTOMER *temp = newCustomer();
    temp->nextCustomer = *head;
    *head = temp;
}

extern void pop (CUSTOMER **head)
{
    CUSTOMER *tempPtr = *head;
    if (tempPtr != NULL)
    {
        head = &tempPtr->nextCustomer;
        free(tempPtr);
    }
}

extern void printQueue (CUSTOMER *head)
{
    while(head != NULL)
    {
        printf("Customer is %s\n", head->status);
        head = head->nextCustomer;
    }
}

extern void emptyQueue (CUSTOMER **root)
{


}