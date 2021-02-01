#include "simQ.h"

void readInputFile (char *inputFileName)
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

void checkParameters (int amountOfArgs)
{
    if (amountOfArgs < 3) 
    {
        printf("There's not enough args\n");
        exit(-1);
    }
}

// Main Method
int main(int argc, char **argv)
{
    CUSTOMER *queue = NULL;
    push(&queue, 1);
    push(&queue, 2);
    printQueue(queue);
    pop(&queue);
    pop(&queue);
    printQueue(queue);
	return 0;
}
