/*  File: route-records.c
    Flight Records Project
    Matthew Anderson  */

// Include the header
#include "route-records.h"

int main( int argc, char *argv[] ) //
{
    /* 1. Declare variables here */
    char buffer[5];
    int searchChoice = 0;
    char keyChoice1[4];
    char keyChoice2[4];
    int uniqueRoutes;
    FILE* userFile;
    RouteRecord* recordArray;

    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if ( argc < 2 )
    {
        printf( "[ERROR] Missing Command Line Argument: FILENAME...\n" );
        return 1;
    }

    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    printf( "Opening %s...\n", argv[1] );
    userFile = fopen( argv[1], "r" );

    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if ( userFile == NULL )
    {
        printf( "ERROR: Could not open file...\n" );
        return 1;
    }

    /* 5. Do the following to load the records into an array of RouteRecords

            5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    */
    recordArray = createRecords( userFile );
    if ( recordArray == NULL )
    {
        printf( "Error Creating Array...\n" );
        return 1;
    }

    /*
            5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    */
    uniqueRoutes = fillRecords( recordArray, userFile );
    printf( "Unique routes operated by airlines: : %d\n\n", uniqueRoutes );

            //5.3 Close the the file.
    fclose( userFile );

      //6. Create an infinite loop that will do the following:
    while ( 1 )
    {
        //6.1 Call printMenu()
        printMenu();

        //6.2 Ask the user to input a value for the menu
        fscanf( stdin, "%2s", buffer );

        //6.3 Convert the input to an integer
        // Convert user input to an integer and will be handled by the switch if user enters invalid input.
        searchChoice = atoi( buffer );

        //6.4 Create a switch/case statement to handle all the menu options
        switch ( searchChoice )
        {
        //6.4.1 Each option requires the user to enter a search key
            case ROUTE:
                // User inputs origin
                printf( "Enter origin: " );
                fscanf( stdin, "%3s", keyChoice1 );

                // User inputs destination
                printf( "Enter destination: " );
                fscanf( stdin, "%3s", keyChoice2 );

                // Call searchRecords with ROUTE as the search type
                printf( "\nSearching by route...\n" );
                searchRecords( recordArray, uniqueRoutes, keyChoice1, keyChoice2, ROUTE );

                // End case
                break;

            case ORIGIN:
                // User inputs origin
                printf( "Enter origin: " );
                fscanf( stdin, "%3s", keyChoice1 );

                // Call searchRecords with ORIGIN as the search type || Passes Null for keyChoice2
                printf( "\nSearching by origin...\n" );
                searchRecords( recordArray, uniqueRoutes, keyChoice1, NULL, ORIGIN );

                // End case
                break;

            case DESTINATION:
                // User inputs origin
                printf( "Enter destination: " );
                fscanf( stdin, "%s", keyChoice1 );

                // Call searchRecords with ORIGIN as the search type || Passes NULL for KeyChoice2
                printf( "\nSearching by destination...\n" );
                searchRecords( recordArray, uniqueRoutes, keyChoice1, NULL, DESTINATION );

                // End case
                break;

            case AIRLINE:
                // User inputs origin
                printf( "Enter airline: " );
                fscanf( stdin, "%s", keyChoice1 );

                // Call searchRecords with ORIGIN as the search type || Passes NULL for KeyChoice2
                printf( "\nSearching by origin...\n" );
                searchRecords( recordArray, uniqueRoutes, keyChoice1, NULL, AIRLINE );

                // End case
                break;

        // Ends the program if the user enters 5
            case QUIT:
                printf( "Good-bye!\n" );
                free( recordArray );
                
                return 0;

        // Default is executed in the event user enters bad input.
            default:
                // Notify the user of an invalid input
                printf( "Invalid choice...\n" );
                continue;
        }
    }
}
