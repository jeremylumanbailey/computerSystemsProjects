////////////////////////////////////////////////////////////////////////////////
//
//  File          : cmsc257-s16-assign2.c
//  Description   : This is the main code file for the CMSC257 assignment 2.
//                  see class assignment for details on what needs to be added.
//
//  Author        : Jeremy Bailey
//  Created       : Febuary 2019
//


// Include Files


// Project Includes
#include "a2support.h"
#include <stdio.h>

// Defines
#define NUMBER_ENTRIES 20 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : This is the main function for the cmsc257-s16-assign2 program.
//
// Inputs       : none
// Outputs      : 0 if successful, -1 otherwise

int main( void ) {
	// Local variables
	float f_array[NUMBER_ENTRIES];
	int i, i_array[NUMBER_ENTRIES];

    printf("Enter 8 numbers ");
    // Read the integer values
	for ( i=0; i<NUMBER_ENTRIES; i++ ) {
	    scanf( "%f", &f_array[i] );
	}
    
    for ( i=0; i<NUMBER_ENTRIES; i++ ) {
        i_array[i] = (int)f_array[i];

        i_array[i] = i_array[i]%16;

        if( i_array[i] < 0 ) {
            i_array[i] = i_array[i] * (-1);
        }
    }

        printf("\n");
//SORRY FOR ALL THE PRINF("\n") STILL FIGURING OUT BEST WAY TO PRINT THINGS TO TERMINAL CLEANLY 
    printf("\n");
    printf("array as floats ");
    float_display_array(f_array, NUMBER_ENTRIES);
    printf("\n");

    printf("\n");
    printf("array as integers ");
    integer_display_array(i_array, NUMBER_ENTRIES);
    printf("\n");
   
    printf("\n");
    printf("Number of ones in each element from binary ");
    for ( i=0; i<NUMBER_ENTRIES; i++ ) {
        printf("%d ", count_bits(i_array[i]));

    }
        printf("\n");
   
        printf("\n");
    printf("Numbers that appear most in array ");
    most_values(i_array, NUMBER_ENTRIES, 15);
        printf("\n");
 
        printf("\n");
    integer_quicksort(i_array,0,(NUMBER_ENTRIES-0));
        printf("\n");

        printf("\n");
    printf("sorted array ");
    integer_display_array(i_array, NUMBER_ENTRIES);
        printf("\n");

        printf("\n");
    printf("Total number of evens in float array ");
    printf("%d", float_evens(f_array, NUMBER_ENTRIES));
        printf("\n");
 
        printf("\n");
    printf("Total number of evens in integer array in range zero to fifteen ");
    printf("%d", integer_evens(i_array, NUMBER_ENTRIES));
        printf("\n");
   
       printf("\n");

    for ( i=0; i<NUMBER_ENTRIES; i++) {
    char biarray[8];
                unsigned short x = (unsigned short)i_array[i];
                printf("Binary form: ");
                    binary_string(x,biarray,8); 
                     
        printf("\n");
                printf("Reverse binary form: ");
                     binary_stringReverse(x,biarray,8);
         printf("\n");
                    
        printf("\n");

    }
        printf("\n");    

unsigned short bubble = 21; //reverse_bits(00000000);
printf("%d",bubble);
// Return successfully
	return(0);
}
