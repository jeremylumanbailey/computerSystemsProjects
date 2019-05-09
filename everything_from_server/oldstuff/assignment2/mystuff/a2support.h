#ifndef A2SUPPORT_INCLUDED
#define A2SUPPORT_INCLUDED

//////////////////////////////////////////////////////////////////////////////
//
//  File          : a2support.h
//  Description   : This is the header file for the functions for assignment
//                  1 of the CMSC257 course.  Students are required to define
//                  the following functions and implement them in another
//                  file, a1support.c.
//
//  Author        : Jeremy Bailey
//  Created       : Febuary 2019

// Functions to define

      void float_display_array(float *displayarrfloat, int array_size);
      void integer_display_array(int *displayarrints, int array_size);
      int float_evens(float *arrfloateven, int array_size);
      int integer_evens(int *arreven, int array_size);
      int count_bits(int bitty);
      void integer_quicksort(int arr[], int first, int last);
      void most_values(int arrvals[], int array_size, int highest);
      unsigned short reverse_bits(unsigned short reversebit);
      void binary_string(unsigned short x, char *arr,  int array_size);
      void binary_stringReverse(unsigned short n,char *arr, int array_size);
#endif

