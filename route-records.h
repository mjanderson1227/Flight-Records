/*  File: route-records.h
    Flight Records Project
    Matthew Anderson  */

// Header Guard
#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

// Included Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros
#define PASSENGER_SIZE 6

/*
    Struct: Route Records
    ---------------------
    Holds information about a route
    that is operated by one airline
*/
typedef struct RouteRecord
{
    char originCode[4];
    char destinationCode[4];
    char airlineCode[3];
    int passengerCounts[PASSENGER_SIZE];
} RouteRecord;


/*
    Enum: SearchType
    ----------------
    Contains values that
    determine what type of
    search the user wishes
    to conduct.
*/
typedef enum SearchType
{
    ROUTE = 1,
    ORIGIN = 2,
    DESTINATION = 3,
    AIRLINE = 4,
    QUIT = 5
} SearchType;


/*
    Function: createRecords
    -----------------------
    Parameters (1):
        1 - FILE* fileIn:
            The address of the data.csv file

    Return Type:
        RouteRecord* - A pointer to an array
        of RouteRecords

    Description:
        function will read the given
        CSV file and dynamically allocate
        an array of RouteRecord structs
        based on the number of lines.
        NOTE - Initialize passengerCount
        to 0.  Skip first line of the file.
*/
RouteRecord* createRecords( FILE* );


/*
    Function: createRecords
    -----------------------
    Parameters (2):
        1 - RouteRecord* r:
            The array of RouteRecords
            created by the function createRecords().

        2 - FILE* fileIn:
            The FILE pointer to data.csv

    Return Type:
        int - The number of RouteRecords
        used in the array.  
        *NOTE - Value returned will
        be less than the size of the array.

    Description:
    Function will parse out the data in the
    data.csv file and store it each index of the array.
    *NOTE - Function depends on findAirlineRoute()
    to find if data for the record exists.
*/
int fillRecords( RouteRecord*, FILE* );


/*
    Function: findAirlineRoute
    --------------------------
    Parameters(6):
        1 - RouteRecord* r:
            The array of route records.

        2 - int length:
            The integer value returned in the
            function call to createRecords().

        3 - const char* origin:
            the origin code of the desired record.

        4 - const char* destination:
            the destination code of the desired record.

        5 - const char* airline:
            the airline code of the desired record.

        6 - int curIdx:
            Used for the recursive base case. [POSSIBLY]

    Return Type:
        int - The index where the three strings appear.
        If they do not appear it will return -1.

    Description:
        *IMPORTANT - THIS IS A RECURSIVE FUNCTION
        Searches through the array of records to 
        find the record that matches the three input 
        strings.
*/
int findAirlineRoute(RouteRecord*, int, const char*, const char*, const char*, int);


/*
    Function: searchRecords
    -----------------------
    Parameters(5):
        1 - RouteRecord* r:
            The array of RouteRecords.

        2 - int length:
            Integer value returned by createRecords().

        3 - const char* key1:
            The value that the user is looking for.

        4 - const char* key2:
            The other value that the user is looking for.

        5 - SearchType st:
            The value that the user wants to search by.
            Key 1 & 2 will depend on this value.

    *No Return Type*

    Description:
        Prints out the aiirline and the route for each matching value.
        Followed by the total number of passengers by month for all
        matching records, as well as average number of passengers per
        month.
        *NOTE - Instances where search yields 0 results must be handled.
*/
void searchRecords( RouteRecord*, int, const char*, const char*, SearchType);


/*
    Function: printMenu()
    ---------------------
    *No Parameters*

    *No Return Type*

    Description:
    Prints the menu of options that the user can choose from.

    Formatting Example:
        ######### Airline Route Records Database MENU #########
        1. Search by Route
        2. Search by Origin Airport
        3. Search by Destination Airport
        4. Search by Airline
        5. Quit
        Enter your selection: 
*/
void printMenu();


#endif