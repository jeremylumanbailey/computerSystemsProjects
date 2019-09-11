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
//void *last = 0x0;
//void *starter = 0x0;


int print_state(void *ptr, int size ) {
	printf("Start of Space: %p\n", ptr);
	printf("End of Space: %p\n", ptr + size);
	
	int leakage = 0;
	struct block_meta *block = get_block_ptr(ptr);
	
	leakage = (META_SIZE-block->size);
	printf("Memory Leakage: %d\n", leakage);
		
	void *pt = sbrk(0);
	
//	printf("Current Heap Location: [%p] (%x)\n", pt,(unsigned) (pt-last) );
//	starter=last;
//	last = pt;
	return (0);
}


int main(void) {

	int *item1 = malloc(5* sizeof(int));
	print_state(item1, 5* sizeof(int));



	return 0;
}
