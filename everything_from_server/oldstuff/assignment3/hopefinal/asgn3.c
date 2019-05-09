// Project Includes
#include "stdio.h"
#include "asgn3_support.h"

//////////////////////////////////////////////////////////////////
//
//  Author: Jeremy Bailey
//	March 2019
//	CMSC 257 Assignment 3 
//
//////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// 
//  memleak() prints memory leakage of running program
//	basically (allocated - used)
// 
//	Inputs - *ptr
//
//	Outputs - prints to console
//
///////////////////////////////////////////////////////////////////// 
size_t totalLeak = 0; //Keep track of total memory leakage
void memleak(void *ptr){

int leak = 0;

struct block_meta *block = get_block_ptr(ptr);

leak += (META_SIZE - block->size);

totalLeak += leak;
printf ("Memrory leak is: %d\n", leak);

}
/////////////////////////////////////////////////////////////////
//
//	printMaAddress() prints out beginning of memory address &
//	end of memory address
//
//	Inputs - *ptr, size
//
//	Outputs - prints to console
//
/////////////////////////////////////////////////////////////////
void printMySelf( void *ptr, int size )
{
	printf("Start Address: %p\n",ptr);
	printf("End Address  : %p\n", ptr + size);
	memleak(ptr);
	printf("%s\n","----------------------------");
}

////////////////////////////////////////////////////////////////////
//
//	main() is used as the main function in program
//
//	Input - NOTHING
//
//	Output - 1 for success
//
////////////////////////////////////////////////////////////////////

int main( ) {
printf("%s\n","-------------------------------------");
printf("%s\n","           10 malloc() calls");
printf("%s\n","-------------------------------------");

 void *start = sbrk(0);

 int *m1= malloc(2* sizeof(int));
 printMySelf(m1,2* sizeof(int));

 int *m2= malloc(2* sizeof(int));
 printMySelf(m2,2* sizeof(int));

 int *m3= malloc(2* sizeof(int));
 printMySelf(m3,2* sizeof(int));

 int *m4= malloc(2* sizeof(int));
 printMySelf(m4,2* sizeof(int));

 int *m5= malloc(2* sizeof(int));
 printMySelf(m5,2* sizeof(int));

 int *m6= malloc(2* sizeof(int));
 printMySelf(m6,2* sizeof(int));

 int *m7= malloc(2* sizeof(int));
 printMySelf(m7,2* sizeof(int));

 int *m8= malloc(2* sizeof(int));
 printMySelf(m8,2* sizeof(int));

 int *m9= malloc(2* sizeof(int));
 printMySelf(m9,2* sizeof(int));

 int *m10= malloc(2* sizeof(int));
 printMySelf(m10,2* sizeof(int));

  int *m11= malloc(3* sizeof(int));
 printMySelf(m11,3* sizeof(int));

  int *m12= malloc(5* sizeof(int));
 printMySelf(m12,5* sizeof(int));

  int *m13= malloc(6* sizeof(int));
 printMySelf(m13,6* sizeof(int));

  int *m14= malloc(7* sizeof(int));
 printMySelf(m14,7* sizeof(int));

  int *m15= malloc(3* sizeof(int));
 printMySelf(m15,3* sizeof(int));


printf("%s\n","-------------------------------------");
printf("%s\n","           10 calloc() calls");
printf("%s\n","-------------------------------------");

int *c1= calloc(9, sizeof(int));
 printMySelf(c1,9* sizeof(int));

 int *c2= calloc(5, sizeof(int));
 printMySelf(c2,5* sizeof(int));

int *c3= calloc(4, sizeof(int));
 printMySelf(c3,4* sizeof(int));

int *c4= calloc(3, sizeof(int));
 printMySelf(c4,3* sizeof(int));

int *c5= calloc(4, sizeof(int));
 printMySelf(c5,4* sizeof(int));

int *c6= calloc(9, sizeof(int));
 printMySelf(c6,9* sizeof(int));

int *c7= calloc(7, sizeof(int));
 printMySelf(c7,7* sizeof(int));

int *c8= calloc(4, sizeof(int));
 printMySelf(c8,4* sizeof(int));

int *c9= calloc(6, sizeof(int));
 printMySelf(c9,6* sizeof(int));

int *c10= calloc(8, sizeof(int));
 printMySelf(c10,8* sizeof(int));

printf("%s\n","-------------------------------------");
printf("%s\n","           10 realloc() calls"		 );
printf("%s\n","-------------------------------------");

int *real1= realloc(m1,4* sizeof(int));
printMySelf(real1,4* sizeof(int));

int *real2= realloc(m2,2* sizeof(int));
printMySelf(real2,2* sizeof(int));

int *real3= realloc(m3,2* sizeof(int));
printMySelf(real3,2* sizeof(int));

int *real4= realloc(m4,4* sizeof(int));
printMySelf(real4,4* sizeof(int));

int *real5= realloc(m5,4* sizeof(int));
printMySelf(real5,4* sizeof(int));

int *real6= realloc(m6,4* sizeof(int));
printMySelf(real6,4* sizeof(int));

int *real7= realloc(m7,4* sizeof(int));
printMySelf(real7,4* sizeof(int));

int *real8= realloc(m8,4* sizeof(int));
printMySelf(real8,4* sizeof(int));

int *real9= realloc(m9,4* sizeof(int));
printMySelf(real9,4* sizeof(int));

int *real10= realloc(m10,4* sizeof(int));
printMySelf(real10,4* sizeof(int));

printf("%s\n","-------------------------------------");
printf("%s\n","           5 free() calls			");
printf("%s\n","-------------------------------------");

free(m1);
free(m2);
free(m3);
free(m4);
free(m5);
//----------------------------------------------------

void *end = sbrk(0);

printf("Start of HEAP = %p\n", start);
printf("End of HEAP = %p\n", end);
printf("%s", "Total memory leakage is: ");
printf("%zu",totalLeak);
printf("\n");

return 1;

}
