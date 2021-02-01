#include "simQ.h"

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

    CUSTOMER *root = NULL;
    push(&root);
    push(&root);
    push(&root);
    push(&root);
    printQueue(root);
	return 0;
}
