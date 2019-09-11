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
//  memleak() prints memory leakage of driving running implementation
//	basically allocated - used
// 
//	Inputs - *ptr
//
//	Outputs - prints to console
//
///////////////////////////////////////////////////////////////////// 
void memleak(void *ptr){

int leak = 0;

struct block_meta *block = get_block_ptr(ptr);

if ( block->size < META_SIZE) {
leak+=(META_SIZE-block->size);
}

if ( block->free){

leak+=block->size;

}

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

 int *m1= malloc(2* sizeof(int));
 printMySelf(m1,2* sizeof(int));

free(m1);

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

printf("%s\n","-------------------------------------");
printf("%s\n","           10 calloc() calls");
printf("%s\n","-------------------------------------");

int *c1= calloc(4, sizeof(int));
 printMySelf(c1,4* sizeof(int));

 int *c2= calloc(4, sizeof(int));
 printMySelf(c2,4* sizeof(int));

int *c3= calloc(4, sizeof(int));
 printMySelf(c3,4* sizeof(int));

int *c4= calloc(4, sizeof(int));
 printMySelf(c4,4* sizeof(int));

int *c5= calloc(4, sizeof(int));
 printMySelf(c5,4* sizeof(int));

int *c6= calloc(4, sizeof(int));
 printMySelf(c6,4* sizeof(int));

int *c7= calloc(4, sizeof(int));
 printMySelf(c7,4* sizeof(int));

int *c8= calloc(4, sizeof(int));
 printMySelf(c8,4* sizeof(int));

int *c9= calloc(4, sizeof(int));
 printMySelf(c9,4* sizeof(int));

int *c10= calloc(4, sizeof(int));
 printMySelf(c10,4* sizeof(int));



printf("%s\n","-------------------------------------");
printf("%s\n","           10 realloc() calls");
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


	
	free(m2);
	free(m3);
	free(m4);
	free(m5);

printf("%ld\n",sizeof(struct block_meta));
	
//	printf("%ld\n",sizeof(size_t));

//	printf("%ld\n",sizeof(META_SIZE));

    printf("%ld\nsizeof int: ",sizeof(int));
    printf("%ld\nsizeof char: ",sizeof(char));  
    printf("%ld\nsizeof float: ",sizeof(float)); 
    printf("%ld\nsifeof double: ",sizeof(double)); 

printf("%s\n","asgn3 main ran" );
return 1;

}
