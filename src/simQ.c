#include "simQ.h"

/* Function Definitions */
int getParamValue (char *inputFileName, char parameterName[])
{
    FILE *inputFile;
    char tempStr[30];
    int tempInt;

    /* Check that the file can be opened to be read without errors. */
    if ((inputFile = fopen(inputFileName, "r")) == NULL)
    {
        fprintf(stderr, "Could not open the file. %s\n", __FILE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    /* Iterate through the lines in the file until EOF. */
    while ( !feof(inputFile) )
    {
        /* Scan each line in the file until there is a line with the format of
        [parameterName] [value]. */
        if (fscanf(inputFile, "%s %d", tempStr, &tempInt) == 2)
        {
            /* Check that the name of the parameter is the 
            same as the desired parameter. */
            if ( (strcmp(tempStr, parameterName)) == 0 )
            {
                return tempInt;
            }
        }
    }
    fclose(inputFile);
    exit(EXIT_FAILURE);
}

void createOutputFile (char* outputFileName)
{
    FILE *outputFile;
    if ( (outputFile = fopen(outputFileName, "w")) == NULL )
    {
        fprintf(stderr, "Could not open the file. %s\n", __FILE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void checkParams (int amountOfArgs)
{
    /* Make sure that the program runs if it gets the
    correct amount of arguments. */
    if (amountOfArgs < 3) 
    {
        printf("Not enough args to run.\n");
        exit(EXIT_FAILURE);
    }
}

/* Main Method */
int main(int argc, char **argv)
{
    /* Declare the location of the file and the parameters in the simulation. */
    char *inputFileName, *outputFileName;
    int numSims;

    /* Get parameters from the command line. */
    /* *inputFileName = *argv[1]; */
    /* numSims = atoi(argv[2]); */
    /* *outputFileName = *argv[3]; */
    inputFileName = "data/exampleFileIn.txt";
    numSims = 3;
    outputFileName = "out/outputFile.txt";

    /* Get parameters from input file */
    int maxQueueLength = getParamValue(inputFileName, "maxQueueLength");
    int numServicePoints = getParamValue(inputFileName, "numServicePoints");
    int closingTime = getParamValue(inputFileName, "closingTime");

    int averageCustomerTolerance = getParamValue(inputFileName, "averageCustomerTolerance");
    int maxCustomerTolerance = getParamValue(inputFileName, "maxCustomerTolerance");
    int minCustomerTolerance = getParamValue(inputFileName, "minCustomerTolerance");

    /* How long on average does it take to clear a queue after closing time */
    /* Optimum number of service points required to serve customers */
    /* How many customers on average can be served in a day */
    /* How long on average does each customer wait */
    /* How many customers, on average, give up waiting and leave without being served */
	return EXIT_SUCCESS;
}
