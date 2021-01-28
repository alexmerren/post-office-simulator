#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A FIFO linked list of customers.
 */
struct customer 
{
    unsigned short maxQueueLength;
	unsigned short tolerance;
	char status[12];
	struct customer *nextCustomer;
};
typedef struct customer customer;

/**
 * A service point to serve customers.
 */
struct servicePoint
{
    unsigned short numServicePoints;
	unsigned short number;
};
typedef struct servicePoint servicePoint;

customer* newCustomer()
{
    customer *newCustomer;
    if ( ( newCustomer = (customer *)malloc(sizeof(customer)) ) == NULL )
    {
        printf("Not enough memory!\n");
        exit(-1);
    }
    newCustomer->nextCustomer= NULL;
    return newCustomer;
}

void addCustomer(customer *root)
{
    customer* currentCustomer = root;
    while (currentCustomer->nextCustomer != NULL)
    {
        currentCustomer = currentCustomer->nextCustomer;
    }
    currentCustomer->nextCustomer = newCustomer();
}

void removeCustomer(customer **root)
{
    customer *tempPtr = *root;
    if (tempPtr != NULL)
    {
        *root = tempPtr->nextCustomer;
        free(tempPtr);
    }
}

void readInputFile(char *inputFileName)
{
    FILE *inputFile;
    if ((inputFile = fopen(inputFileName, "r")) == NULL)
    {
        printf("There was an error opening the file %c\n", *inputFileName);
        exit(1);
    }
    // Sort out all the parameter stuff here.
    fclose(inputFile);
}

void checkParameters(int amountOfArgs)
{
    if (amountOfArgs < 3) 
    {
        printf("There's not enough args\n");
        exit(-1);
    }
}

int main(int argc, char **argv)
{
    checkParameters(argc);

    FILE *OutputFile;
    int numSims = atoi(argv[2]);

    // Update the values defined above with the values in the file in the parameters.
    readInputFile(argv[1]);

    // Create a file for the output with a name as defined in the arguments.
    FILE *outputFile = fopen(argv[3], "w");

    // Close the output file.
    fclose(outputFile);
	return 0;
}
