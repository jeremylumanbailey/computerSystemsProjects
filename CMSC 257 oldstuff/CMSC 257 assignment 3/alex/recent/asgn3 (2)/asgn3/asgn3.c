#include "stdio.h"
#include "asgn3_support.h"


//************************************
//Created by Jorge Alex Villavicencio
//For CMSC257 Assignment 3
//
//asgn3.c contains a driver to test the code for assignment 3, 
//facilitating the following function tests:
//10 malloc() calls
//10 calloc() calls
//10 realloc() calls
//5 free() calls
//print total memory leakage of program
//Print starting and ending addresses of the heap
//************************************

void *pt = 0x0;

int main(void) {

	//Begin Malloc Section
        printf("\nMalloc Section:\n");
	int *item1 = malloc(3* sizeof(char));
	pt = print_state(item1, pt);

        int *item2 = malloc(6* sizeof(int));
        pt = print_state(item2, pt);
	
	int *item3 = malloc(3* sizeof(int));
        pt = print_state(item3, pt);

        int *item4 = malloc(3* sizeof(int));
        pt = print_state(item4, pt);
	
        int *item5 = malloc(3* sizeof(int));
        pt = print_state(item5, pt);
        
	int *item6 = malloc(3* sizeof(int));
        pt = print_state(item6, pt);

        int *item7 = malloc(3* sizeof(int));
        pt = print_state(item7, pt);

        int *item8 = malloc(3* sizeof(int));
        pt = print_state(item8, pt);

        int *item9 = malloc(3* sizeof(int));
        pt = print_state(item9, pt);

        int *item10 = malloc(3* sizeof(int));
        pt = print_state(item10, pt);

        //Begin calloc section
        printf("\nCalloc Section:\n");
	int *item1a = calloc(3, sizeof(char));
        pt = print_state(item1a, pt);

        int *item2a = calloc(6, sizeof(int));
        pt = print_state(item2a, pt);

        int *item3a = calloc(3, sizeof(int));
        pt = print_state(item3a, pt);

        int *item4a = calloc(3, sizeof(int));
        pt = print_state(item4a, pt);

        int *item5a = calloc(3, sizeof(int));
        pt = print_state(item5a, pt);

        int *item6a = calloc(3, sizeof(int));
        pt = print_state(item6a, pt);

        int *item7a = calloc(3, sizeof(int));
        pt = print_state(item7a, pt);

        int *item8a = calloc(3, sizeof(int));
        pt = print_state(item8a, pt);

        int *item9a = calloc(3, sizeof(int));
        pt = print_state(item9a, pt);

        int *item10a = calloc(3, sizeof(int));
        pt = print_state(item10a, pt);

	//Begin realloc section
	printf("\nRealloc Section:\n");
	int *item1b = realloc(item1, 3* sizeof(char));
        pt = print_state(item1b, pt);

        int *item2b = realloc(item2, 3* sizeof(int));
        pt = print_state(item2b, pt);

        int *item3b = realloc(item3, 3* sizeof(int));
        pt = print_state(item3b, pt);

        int *item4b = realloc(item4, 3* sizeof(int));
        pt = print_state(item4b, pt);

        int *item5b = realloc(item5, 3* sizeof(int));
        pt = print_state(item5b, pt);

        int *item6b = realloc(item6, 3* sizeof(int));
        pt = print_state(item6b, pt);

        int *item7b = realloc(item7, 3* sizeof(int));
        pt = print_state(item7b, pt);

        int *item8b = realloc(item8, 3* sizeof(int));
        pt = print_state(item8b, pt);

        int *item9b = realloc(item9, 3* sizeof(int));
        pt = print_state(item9b, pt);

        int *item10b = realloc(item10, 3* sizeof(int));
        pt = print_state(item10b, pt);

	//Begin Free Section
	printf("\nFree Section:\n");
        free(item1);
        pt = print_state(item1, pt);

        free(item2);
        pt = print_state(item2, pt);

        free(item3);
        pt = print_state(item3, pt);

        free(item4);
        pt = print_state(item4, pt);

        free(item5);
        pt = print_state(item5, pt);
	
	//Print total memory leakage
	total_memory_leakage();	
	
	return 0;
}
