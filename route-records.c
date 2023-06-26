/*  File: route-records.c
    Flight Records Project
    Matthew Anderson  */

// Include header
#include "route-records.h"



RouteRecord* createRecords( FILE* fileIn ) 
{
    // Declare for loop value
    int i;
    int j;

    // [Return Value] Pointer to the array that will be created
    RouteRecord* recordArray = NULL;

    // Count for the number of lines in the CSV
    int count = 0;

    // Skip the first line of the file
    fseek( fileIn, 41, SEEK_SET );

    // While not at the end of file
    while ( !feof( fileIn ) )
    {
               //If the current character is a line break.
        if ( fgetc( fileIn ) == '\n' )
        {
            //increment count by one
            ++count;
        }
    }

    // Allocate memory to the array
    recordArray = ( RouteRecord* ) malloc( sizeof( RouteRecord ) * count );

    // Loop through the array
    for ( i = 0; i < count; i++ )
    {
        // Set all the passenger values of each RouteRecord to 0
        for ( j = 0; j < PASSENGER_SIZE; j++ )
        {
            recordArray[i].passengerCounts[j] = 0;
        }
    }

    // Rewind the File Pointer
    rewind( fileIn );

    // Return the filled array
    return recordArray;
}



int fillRecords( RouteRecord* r, FILE* fileIn )
{
    // Buffer for the line
    char buffer[45];

    // Integer to store the index of previously stored records using the findAirlineRoute recursive Search
    int originalRecord;

    // [Return Value] The Number of records.  Incremented every time a record is added
    int numRecords = 0;

    // Month identifies where in the array to place/add the passenger count
    int month;

    // the number to add to the passenger count to the corresponding month
    int currentPassengers;

    // Currently read struct values
    char currentOriginCode[4];
    char currentDestinationCode[4];
    char currentAirlineCode[3];

    // Seek the first piece of actual data in the CSV i.e skipping the first line
    fseek( fileIn, 41, SEEK_SET );

    while ( !feof( fileIn ) )
    {
        // Read the line into the buffer
        fgets( buffer, 45, fileIn );

        // Scans into the current record
        sscanf( buffer, "%d,%[^,],%[^,],%[^,],Passengers,%d\n", &month, currentOriginCode, currentDestinationCode, currentAirlineCode, &currentPassengers );
        
        // Decrement the value that corresponds to an array index
        month--;

        // Defining the value of originalRecord with the int returned from the recursive search
        originalRecord = findAirlineRoute( r, 0, currentOriginCode, currentDestinationCode, currentAirlineCode, numRecords );

        // Logic to handle if the current record already exists
        // If record does exist, then add it to the array
        if ( originalRecord != -1 )
        {
            r[originalRecord].passengerCounts[month] += currentPassengers;
        }

        // Otherwise the record does not exist, add new RouteRecord data to the current index and increment numRecords
        else 
        {
            strcpy( r[numRecords].originCode, currentOriginCode );
            strcpy( r[numRecords].destinationCode, currentDestinationCode );
            strcpy( r[numRecords].airlineCode, currentAirlineCode );
            r[numRecords].passengerCounts[month] += currentPassengers;
            ++numRecords;
        }
    }
    return numRecords;
}



int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx)
{
    // Stores the return value: Either the index of the found Record or -1.
    int temp;

    // Base Cases
    if ( strcmp( r[curIdx].originCode, origin ) == 0 && strcmp( r[curIdx].destinationCode, destination ) == 0 && strcmp( r[curIdx].airlineCode, airline ) == 0 )
    {
        return curIdx;
    }

    // Base case if the record does not already exist.
    else if ( curIdx <= length )
    {
        return -1;
    }
    
    // Recursive call that assigns temp to the return value of each subsequent return value.
    temp = findAirlineRoute( r, length, origin, destination, airline, curIdx-1 );
    
    // Return the index (either that of found record or -1) down the callstack.
    return temp;
}



void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st )
{
    // Variable used to loop through the array of RouteRecords
    int i;

    // Variable used to loop through the array of passengers inside of each RouteRecord object
    int j;

    // Used to track the number records that match the given input
    int numRecords = 0;

    // Array stores the total passenger per month
    int totalMonthlyPassengers[PASSENGER_SIZE] = {0,0,0,0,0,0};

    // Variable stores the total overall passengers
    int totalPassengers = 0;

    // Variable used to store the average passengers per month calculated below
    int averagePassengers;

    // Loops through entire array
    for ( i = 0; i < length; i++ )
    {
        // if statements that check if the current record matches the search type.
        /*
            for each match:
            prints the route airline code followed by origin and destination code
            adds the number of passengers for each index of the array to the total
            adds the number of passengers in each index of the passengerCounts array to the current index of totalMonthlyPassengers array.
        */
        // Branch executes when user searches by ROUTE
        if ( st == ROUTE && strcmp( r[i].originCode, key1 ) == 0 && strcmp( r[i].destinationCode, key2) == 0 )
        {
            printf("%s (%s-%s) ", r[i].airlineCode, r[i].originCode, r[i].destinationCode);
            for ( j = 0; j < PASSENGER_SIZE; j++ )
            {
                totalPassengers += r[i].passengerCounts[j];
                totalMonthlyPassengers[j] += r[i].passengerCounts[j];
            }
            numRecords++;
        }

        // Branch executes when searching by ORIGIN
        if ( st == ORIGIN && strcmp( r[i].originCode, key1 ) == 0 )
        {
            printf("%s (%s-%s) ", r[i].airlineCode, r[i].originCode, r[i].destinationCode);
            for ( j = 0; j < PASSENGER_SIZE; j++ )
            {
                totalPassengers += r[i].passengerCounts[j];
                totalMonthlyPassengers[j] += r[i].passengerCounts[j];
            }
            numRecords++;
        }

        // Branch executes when searching by DESTINATION
        if ( st == DESTINATION && strcmp( r[i].destinationCode, key1 ) == 0 )
        {
            printf( "%s (%s-%s) ", r[i].airlineCode, r[i].originCode, r[i].destinationCode );
            for ( j = 0; j < PASSENGER_SIZE; j++ )
            {
                totalPassengers += r[i].passengerCounts[j];
                totalMonthlyPassengers[j] += r[i].passengerCounts[j];
            }
            numRecords++;
        }

        // Branch executes when searching by AIRLINE
        if ( st == AIRLINE && strcmp( r[i].airlineCode, key1 ) == 0 )
        {
            printf( "%s (%s-%s) ", r[i].airlineCode, r[i].originCode, r[i].destinationCode );
            for ( j = 0; j < PASSENGER_SIZE; j++ )
            {
                totalPassengers += r[i].passengerCounts[j];
                totalMonthlyPassengers[j] += r[i].passengerCounts[j];
            }
            numRecords++;
        }
    }

    // Calculating the average passengers
    averagePassengers = totalPassengers / 6;

    // Printing the output
    // If no matches are found the program will let the user know
    if ( numRecords == 0 )
    {
        printf( "No matches were found.\n" );
        return;
    }

    // Prints total matches
    printf( "\n%d matches were found.\n\n", numRecords );

    // Labels the statistics section
    printf( "Statistics\n" );

    // Prints the total passengers
    printf( "Total Passengers: %11d\n", totalPassengers );

    // Prints total passengers for each month
    for ( i = 0; i < PASSENGER_SIZE; i++ )
    {
        printf( "Total Passengers in Month %d: %11d\n", i+1, totalMonthlyPassengers[i] );
    }

    // Printing average passengers
    printf( "\nAverage Passengers per Month: %11d", averagePassengers );
}



void printMenu()
{
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}