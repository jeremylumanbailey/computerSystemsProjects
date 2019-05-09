//////////////////////////////////////////////////////////////////////////////
//
//  File          : a2support.c
//  Description   : This is the support file for the functions for assignment
//                  2 of the CMSC257 course.
//
//
//
//  Author        : Jeremy Bailey
//  Created       : Febuary 2019

// Include Files
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include "a2support.h"

// Function Implementations

/*
#-----------------------------------------------------------------------------------------------------------------------#
# float_display_array() is used print out all the values of a float array on a single line using a for loop and printf. #
# When printing, only the first two values to the right of the decimal point are shown.                                 #
#                                                                                                                       #
#Input - A reference to a float array, The legnth of the array as an int                                                #
#Output - Prints values of an array of floats to the terminal on a single line.                                         #
#-----------------------------------------------------------------------------------------------------------------------#
*/  
void float_display_array(float *displayarrfloat, int array_size) {
    int i;
    for( i=0; i<array_size; i++) {
    
        printf("%.2f \t  ", displayarrfloat[i]);
    }
    }
/*
#---------------------------------------------------------------------------------------------------------------------------#
# integer_display_array() is used to print out all the values of an int array on a single line, using a for loop and printf.#
#                                                                                                                           #
#Input - A reference to an int array, the legnth of the array as an int                                                     #
#Output - Prints array of ints to terminal                                                                                  #
#---------------------------------------------------------------------------------------------------------------------------#
*/
void integer_display_array(int *displayarrints, int array_size) {
    int i;
    for( i=0; i<array_size; i++) {

        printf("%d \t  ", displayarrints[i]);
    }
    }
/*
#----------------------------------------------------------------------------------#
#  count_bits() counts the number of bits in the binary form of the integer given. #
#  This is done using bitwise operators in a while loop.                           #
#Input - An int                                                                   #
#Output - Returns number of "1" bits in binary representation of given int        #
#----------------------------------------------------------------------------------#
*/
   int count_bits(int bitty) {
    int oneOccur = 0;

    while (bitty) {
 
        oneOccur += bitty & 1;
        bitty >>= 1;
    }

        return oneOccur;
   }

/*
#-------------------------------------------------------------------------------#
# integer_evens() is used to count the number of even integers in an int array. #
# It uses modulus conditional to check if an integer is even or not.            #
#                                                                               #
#Input - Reference to an int array, length of array as an int                   #
#Output - Return number of even ints in the array                               #
#-------------------------------------------------------------------------------#
*/ 
   int integer_evens(int *arreven, int array_size) {
       int i;
       int count = 0;
        for( i=0; i<array_size; i++) {
        
            if(arreven[i] % 2 == 0) {
                count++;
            }

        }
        return count;
   }

/*
#-------------------------------------------------------------------------------------------------------#
# float_evens() is used to count the number of even numbers in a float array.                           #
# It casts the float elements to ints so that it can use modulo division to check if it is even or not. #
#                                                                                                       #
#Input - Reference to a float array, length of the array as an int                                      #
#Output - Return number of even floats in the array                                                     #
#-------------------------------------------------------------------------------------------------------#
*/ 
    
   int float_evens(float *arrfloateven, int array_size) {
    
       int i, toInt;
       int count = 0;
        for( i=0; i<array_size; i++) {
            toInt = (int)arrfloateven[i];
            if(toInt % 2 == 0) {
                count++;
            }
        }
    return count;
   }
/*
#-----------------------------------------------------------------------------------------#
# swap() is used to swap to value of two integers.                                        #
# In this program, it is only used to assist with the partition() function's job          #
#                                                                                         #
#Input - int to be swapped, int to be held temporarily                                    #
#Output - Sets first int to second previous second int, sets second int to a placeholder  #
#-----------------------------------------------------------------------------------------#
*/ 
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}




/*
#-----------------------------------------------------------------------------------------------------------------------#
# partition() is used to partition an array of ints into two parts to be sorted to the left or right of the pivot.      #
# It uses a pivot position to sort around. So if our pivot was "5" it cycle through and every element that is < 5 would #
# placed to the left of 5, and every element that is > 5 would be placed to the right of 5.                             #
#                                                                                                                       #
#Input - Reference to an int array, left index of array to start sorting, last index of array                           #
#Output - Returns the value of the next pivot to use                                                                    #
#-----------------------------------------------------------------------------------------------------------------------#
*/
int partition (int arr[], int begin, int end)
{
    int pivot = arr[end];
    int j = begin;
    int i;
    for (i=begin; i<=end-1;i++)
    {
        if (arr[i]< pivot)
        {
         
            if(j != i)
            swap(&arr[j], &arr[i]);
       
            j++;
        }
    }
    swap(&arr[j], &arr[end]);
            return j;
    }




/*
#--------------------------------------------------------------------------------------------------------------#
# integer_quicksort() is used to sort an array from smallest to greatest using the quicksort algorithm.        #
# It uses recursion to accomlish this task. This allows it to divide and conquer the problem. Most of the work #
#  for the sorting is done in the partition() function.                                                        #
#                                                                                                              #
#Input - Reference to an int array, left index of array to start sorting, last index of array                  #
#Output - Sorts the integer array from least to greatest                                                       #
#--------------------------------------------------------------------------------------------------------------#
*/ 
void integer_quicksort(int array[], int low, int high)
{
    int partitioned;
if (low < high)
{
    partitioned = partition(array, low, high);

    integer_quicksort(array, low,partitioned-1);
    integer_quicksort(array,partitioned+1, high);
    }
}

/*
#--------------------------------------------------------------------------------------------------------#
# most_values() find what value(s) occur most frequently, and then prints them to the terminal.          #
# It uses an array of the same length that is set to zero, and cycles through the array to find the      #
# number of occurences the number appears. If it finds one or more appears most, it prints those values. # 
#                                                                                                        #
#Input - Reference to an int array, legnth of array as int, highest value possible value in array        #
#Output - Prints outs the value(s) that occur most frequently                                            #
#--------------------------------------------------------------------------------------------------------#
*/ 
   void most_values(int arrvals[], int element, int highest) {

       int i;
       int countarr[highest + 1];
       int most=0;

        for (i=0;i<(highest+1);i++)
        {
            countarr[i]=0;
        }

        for (i=0;i<element;i++)
        {
            countarr[arrvals[i]]++;
        }

        for (i=0;i<(highest+1);i++)
        {
            if(countarr[i] > most)
                most=countarr[i];
        }

        for (i=0; i<(highest+1); i++) 
        {
            if (countarr[i]==most)
            {
                printf("%d ",i);
            }
        }
   }



/*
#------------------------------------------------------------------------------------------- ------------#
# binary_string() is used to print out the binary form of the number we give the function.               #
# It uses a while loop with modulus division to break down the decimal number into binary form (1 or 0). #
# It then places the binary character into the char array in the for loop.                               #
#                                                                                                        #
#Intput - unsigned short number we want binary of, char array to hold binary representation of number,   #
# int for the size of the char array                                                                     #
#Output - Prints out the binary representation of the number we give the function.                       #
#------------------------------------------------------------------------------------------------------- #
*/
    void binary_string(unsigned short bitty,char *arr, int array_size)
{
    int i = 0;

    while (bitty > 0) {
        arr[i] = bitty % 2;
        bitty = bitty / 2;
        i++;
    }

    for( i=array_size-1; i>=0; i--) {

        printf("%d \t ", arr[i]);
    }
  //  arr[array_size] = "\0";

    int x;

    for ( i=0;i<8; i++) x=x*10 + arr[i]-'0';

printf("%d", x);

 }
/*
#------------------------------------------------------------------------------------------- ------------#
# binary_stringReverse() is used to print out the reverse binary form of the number we give the function.#
# It uses a while loop with modulus division to break down the decimal number into binary form (1 or 0). #
# It then places the binary character into the char array in the for loop.                               #
#                                                                                                        #
#Intput - unsigned short number we want binary of, char array to hold binary representation of number,   #
# int for the size of the char array                                                                     #
#Output - Prints out the reverse binary representation of the number we give the function.               #
#------------------------------------------------------------------------------------------------------- #
*/
  void binary_stringReverse(unsigned short bitty,char *arr, int array_size)
{
    int i = 0;

    while (bitty > 0) {
        arr[i] = bitty % 2;
        bitty = bitty / 2;
        i++;
    }

  for( i=0; i<array_size; i++) {
        printf("%d \t  ", arr[i]);
    }

}

/*
#------------------------------------------------------------------#
#reverse_bits() is used to return the decimal value of an unsigned short bits.
#It uses sizeof() to find memory amount "bits", it sets "y" to double that amount
# and uses "y" as an termination for the loop. "mirror" is shifted left and "bits" 
# shifted right until termination of for loop is reached.
#
#Input - unsigned short bits
#Output - unsigned short reverse
#------------------------------------------------------------------#
*/
  unsigned short reverse_bits(unsigned short bits ) {

int x,y;
y= sizeof(bits)*2;
unsigned short mirror=0;

for (x=0; x<y; x++)  
    {
    mirror=mirror<<1; 
    mirror=mirror|(bits&1); 
    bits=bits>>1;  
    }
return mirror;

  }
  



