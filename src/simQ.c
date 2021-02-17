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
        fprintf(stderr, "Could not open the file. %s\n", inputFileName);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    /* Iterate through the lines in the file until reaching EOF. */
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
    /* If there is not match to the parameter value 
    in the file, exit the program. */
    fclose(inputFile);
    exit(EXIT_FAILURE);
}

void createOutputFile (char *outputFileName)
{
    FILE *outputFile = NULL;
    /* If there is an error creating an output file, exit the program. */
    if ( (outputFile = fopen(outputFileName, "w")) == NULL )
    {
        fprintf(stderr, "There is a file called %s already\n", outputFileName); 
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    /* If output file can be created, write to it, then close it. */
    fputs("# Output file:\n", outputFile);
    fflush(outputFile);
    fclose(outputFile);
}

void checkParams (int amountOfArgs)
{
    /* Make sure that the program runs if it gets the
    correct amount of arguments. */
    if (amountOfArgs < 3) 
    {
        printf("./simQ [inputFileName] [numberOfSims] [outputFileName]\n");
        fprintf(stderr, "Could not open the file %s\n", __FILE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    /* Get parameters from the command line. */
    char *inputFileName = argv[1];
    int numSims = atoi(argv[2]);
    char *outputFileName = argv[3];

    /* Get the standard parameters from the input file. */
    int maxQueueLength = getParamValue(inputFileName, "maxQueueLength");
    int numServicePoints = getParamValue(inputFileName, "numServicePoints");
    int closingTime = getParamValue(inputFileName, "closingTime");

    /* Get the custom parameters from the input file. */
    int minWaitingTime = getParamValue(inputFileName, "minWaitingTime");
    int maxWaitingTime = getParamValue(inputFileName, "maxWaitingTime");
    int minProcessTime = getParamValue(inputFileName, "minProcessTime");
    int maxProcessTime = getParamValue(inputFileName, "maxProcessTime");
    int maxCustomersAdded = getParamValue(inputFileName, "maxCustomersAdded");
    int minCustomersAdded = getParamValue(inputFileName, "minCustomersAdded");

    /* Create the average total variables. */
    int averageTotalFulfilled = 0;
    int averageTotalUnfulfilled = 0;
    int averageTotalTimedout = 0;

    /* Set up the random number generator for later. */
    const gsl_rng_type *T = gsl_rng_mrg;
    gsl_rng *r;
    gsl_rng_env_setup();
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, time(NULL));

    /* Create and open the output file so we can write to it. */    
    createOutputFile(outputFileName);
    FILE *outputFile;
    if ( (outputFile = fopen(outputFileName, "a")) == NULL )
    {
        fprintf(stderr, "Could not open the file %s\n", outputFileName);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "minWaitingTime: %d, maxWaitingTime: %d\n"
                        "minProcessTime: %d, maxProcessTime: %d\n"
                        "minCustomersAdded: %d, maxCustomersAdded: %d\n"
                        "maxQueueLength: %d, numServicePoints: %d, closingTime: %d\n\n",
                        minWaitingTime, maxWaitingTime, minProcessTime, maxProcessTime,
                        minCustomersAdded, maxCustomersAdded, maxQueueLength,
                        numServicePoints, closingTime);

    int intervalNumber = 0, counter;
    /* We will complete numSims amount of simulations with this for loop. */
    for (counter = 0; counter < numSims; counter++)
    {
        /* Create a string that will be used to write to the output file. */
        char stringToWrite[128]; 

        /* Create a starting queue and service point for every simulation. */
        CUSTOMER *queue = NULL;
        SERVICE *servicePoints = NULL;

        /* Create the counters for the information we want out of the simulation. */
        int totalUnfulfilled = 0;
        int totalFulfilled = 0;
        int totalTimedOut = 0;
        int overtime;
        int averageWaitingTime = 0;
        int unfulfilledCustomers;

        /* If the queue is empty, and the intervalNumber is after the
        closing time, the simulation will stop. */
        while (intervalNumber < closingTime || sizeOfQueue(queue) != 0 || amountBeingServed(servicePoints) != 0) 
        {
            intervalNumber++;
            int iter;
            /* Add the amount of service points entered in the input file. */
            for (iter = 0; iter < numServicePoints; iter++)
            {
                addServicePoint(&servicePoints, iter);
            }

            if (numSims == 1)
            {
                /* Write the time interval number in the output file. */
                sprintf(stringToWrite, "Time: %d\n", intervalNumber);
                fprintf(outputFile, "%s", stringToWrite);

                /* Write the amount of customers being served to the output file. */
                sprintf(stringToWrite, "\tAmount of customers being served: %d\n", amountBeingServed(servicePoints));
                fprintf(outputFile, "%s", stringToWrite);

                /* Write the amount of customers in the queue to the output file. */
                sprintf(stringToWrite, "\tAmount of customers in the queue: %d\n", sizeOfQueue(queue));
                fprintf(outputFile, "%s", stringToWrite);

                /* If the interval number is the same as the closing time,
                it has reached closing time. */
                if (intervalNumber == closingTime)
                {
                    fprintf(outputFile, "%s", "# It has reached closing time.\n");
                }
            }
            /* If the interval is before the closing time, 
            then a customer may join the queue. */
            if ( intervalNumber <= closingTime )
            {
                unsigned short randomNumber = gsl_rng_get(r);
                /* Use the random number generator to get a number between the
                maximum and minimum values of customers added. */
                int amountOfCustomersAdded = randomNumber % (maxCustomersAdded - minCustomersAdded + 1) + minCustomersAdded;
                for (iter = 0; iter < amountOfCustomersAdded; iter++)
                {
                    /* If the maximum queue length has been reached,
                    don't add any more people to the queue. */
                    if ( sizeOfQueue(queue) < maxQueueLength )
                    {
                        /* Use the random number generator to get a number
                        between the two limits of the waiting time and
                        process time. */
                        unsigned short waitingTime = randomNumber % (maxWaitingTime - minWaitingTime + 1) + minWaitingTime; 
                        unsigned short processTime = randomNumber % (maxProcessTime - minProcessTime + 1) + minProcessTime; 
                        addToQueue(&queue, waitingTime, processTime);
                        unfulfilledCustomers = amountOfCustomersAdded - iter;
                    } 
                    else 
                    {
                        totalUnfulfilled += unfulfilledCustomers;
                        break;
                    }
                }
            }

            SERVICE *currentServicePoint = servicePoints;
            CUSTOMER *currentCustomer = queue;

            /* Go through all the service points and fill them up with customers. */
            while ( amountBeingServed(servicePoints) != numServicePoints && currentServicePoint != NULL )
            {
                /* If the current service point is not service anyone, remove the first 
                person from the queue and start serving them. */
                if (currentServicePoint->currentCustomer == NULL)
                {
                    currentServicePoint->currentCustomer = removeFromQueue(&queue, NULL);
                }
                currentServicePoint = currentServicePoint->nextServicePoint;
            }

            /* Go through the customers in the queue, and increment their 
            internal counters. If their internal counter has exceeded their
            limit, then they leave the post office, becoming unfulfilled. */
            while (currentCustomer != NULL)
            {
                incrementCounter(currentCustomer);
                if (currentCustomer->counter > currentCustomer->waitingTime)
                {
                    CUSTOMER *leavingCustomer = removeFromQueue(&queue, currentCustomer);
                    leavePostOffice(leavingCustomer);
                    totalTimedOut++;
                }
                currentCustomer = currentCustomer->nextCustomer;
            }

            /* Go through the customers that are being served, and increment
            their internal counters. If their internal counters have exceeded
            the amount of time their task takes, they leave fulfilled.*/
            currentServicePoint = servicePoints;
            while ( currentServicePoint != NULL )
            {
                CUSTOMER *currentCustomer = currentServicePoint->currentCustomer; 
                /* If there is no customer being served at the service point, move on. */
                if ( currentCustomer != NULL )
                {
                    /* If the customer's counter exceeds their process tolerance, remove them. */
                    if ( currentCustomer->counter > currentCustomer->processTime )
                    {
                        currentServicePoint->currentCustomer = NULL;
                        averageWaitingTime += currentCustomer->waitingTime;
                        free(currentCustomer);
                        totalFulfilled++;
                    }
                    /* Always increment all the customer's counters. */
                    incrementCounter(currentCustomer);
                }
                currentServicePoint = currentServicePoint->nextServicePoint;
            }
            if ( numSims == 1)
            {
                fprintf(outputFile, "\tStats during the simulation - Fulfilled: %d, Unfulfilled: %d, Timed-out: %d\n",
                                    totalFulfilled, totalUnfulfilled, totalTimedOut);
            }
        }
        /* Print all the relevant information to the output file. */
        overtime = intervalNumber - closingTime;
        fprintf(outputFile, "Stats - Fulfilled: %d, Unfulfilled: %d, Timed-out: %d, Overtime: %d, Average waiting time: %d\n\n",
                            totalFulfilled, totalUnfulfilled, totalTimedOut, overtime, (averageWaitingTime/totalFulfilled));

        /* Add all the totals to the running averages. */
        averageTotalFulfilled += totalFulfilled;
        averageTotalUnfulfilled += totalUnfulfilled;
        averageTotalTimedout += totalTimedOut;

        /* Reset everything before the next simulation. */
        closeServicePoints(servicePoints);
        intervalNumber = 0;
    }

    /* Print all the averages to the file before finishing. */
    fprintf(outputFile, "Averages -  fulfilled: %d, Average unfulfilled: %d, Average timed-out: %d\n",
            (averageTotalFulfilled/numSims), (averageTotalUnfulfilled/numSims), (averageTotalTimedout/numSims));

    /* Close the output file and free all the pointers from normal operation. */
    free(r);
    fflush(outputFile);
    fclose(outputFile);
	return EXIT_SUCCESS;
}
