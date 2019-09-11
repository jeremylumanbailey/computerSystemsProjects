#include "stdio.h"
// Project Includes
#include "a3support.h"
// 
// // ////////////////////////////////////////////////////////////////////////////////
// // //
// // // Project      : Assignment 3 Memory Management System
// // // Creator      : Liam Fernando 
// // // Class 	      : CMSC 257 Section 1 
// // // 
// // ////////////////////////////////////////////////////////////////////////////////
//

void *last = 0x0;
void *starter = 0x0;

////////////////////////////////////////////////////////////////////////////////////
//
//  Function 	: check_memory
//  Desciption  : checks the memory at the top of the heap. 
//
//  Inputs	: NONE
//  Outputs	: print statement
//
////////////////////////////////////////////////////////////////////////////////////
int check_memory( void )
{
	void *ptr = sbrk(0);
	printf( "The top of the heap is [%p] (%x)\n",ptr,(unsigned) (ptr-last) );
	starter=last;
	last = ptr;
	return (0);
}
	
///////////////////////////////////////////////////////////////////////////////////
// 
//  Function    : Print()
//  Description : prints out address, start, end 
//
//  Inputs	: void *ptr, int size 
//  Outputs     : print statement
//
///////////////////////////////////////////////////////////////////////////////////

void print( void *ptr, int size )
{
	printf("Address:\n");
	printf("Start: %p\n",ptr);
	printf("End: %p\n", ptr + size);
}


///////////////////////////////////////////////////////////////////////////////////
//
//  Function    : memoryleak()
//  Description : prints the memory leaks for each allocation
//
//  Inputs      : void *ptr
//  Outputs     : print statement
//
/////////////////////////////////////////////////////////////////////////////////////


void memoryleak(void *ptr){

int memleak = 0;

struct block_meta *block = get_block_ptr(ptr);

if ( block->size < META_SIZE) {
memleak+=(META_SIZE-block->size);
}

if ( block->free){

memleak+=block->size;

}

printf ("memroy leak is: %d\n\n ", memleak);


}


// 
// ////////////////////////////////////////////////////////////////////////////////
// // 
// //  Function     : main
// //  Description  : This is the main function for the assign3 program.
// //
// //  Inputs       : none
// //  Outputs      : 1 if successful, -1 otherwise
// // 
// ///////////////////////////////////////////////////////////////////////////////
//

int main( ) {

///////////////////////////////////////////////////////////////////////////////////
// PART 2
//-- Using the given code to call 10 mallocs, callocs, reallocs , free
///////////////////////////////////////////////////////////////////////////////////

printf("sbrk(0) = %p\n", sbrk(0));

int *m1= malloc(5* sizeof(int));
print(m1, 5* sizeof(int));
check_memory();
memoryleak(m1);

printf("sbrk(0) = %p\n", sbrk(0));

short *m2= malloc(3*sizeof(short));
print(m1, 3* sizeof(short));
check_memory();
memoryleak(m2);

int *m3= malloc(6*sizeof(int));
print(m1, 6* sizeof(int));
check_memory();
memoryleak(m3);

int *m4= malloc(2*sizeof(int));
print(m1, 2* sizeof(int));
check_memory();
memoryleak(m4);

char *m5= malloc(8*sizeof(char));
print(m1, 8* sizeof(char));
check_memory();
memoryleak(m5);

int *m6= malloc(6*sizeof(int));
print(m1, 6* sizeof(int));
check_memory();
memoryleak(m6);

double *m7= malloc(2*sizeof(double));
print(m1, 2* sizeof(double));
check_memory();
memoryleak(m7);

int *m8= malloc(4*sizeof(int));
print(m1, 4* sizeof(int));
check_memory();
memoryleak(m8);

double *m9= malloc(7*sizeof(double));
print(m1, 7* sizeof(double));
check_memory();
memoryleak(m9);

int *m10= malloc(8*sizeof(int));
print(m1, 8* sizeof(int));
check_memory();
memoryleak(m10);

int *c1= calloc(4,sizeof(int));
print(c1, 4* sizeof(int));
check_memory();
memoryleak(c1);


int *c2= calloc(8,sizeof(int));
print(c2, 8* sizeof(int));
check_memory();
memoryleak(c2);


int *c3= calloc(3,sizeof(int));
print(c3, 3* sizeof(int));
check_memory();
memoryleak(c3);


int *c4= calloc(4,sizeof(int));
print(c4, 4* sizeof(int));
check_memory();
memoryleak(c4);


int *c5= calloc(3,sizeof(int));
print(c5, 3* sizeof(int));
check_memory();
memoryleak(c5);


int *c6= calloc(9,sizeof(int));
print(c6, 9* sizeof(int));
check_memory();
memoryleak(c6);


int *c7= calloc(3,sizeof(int));
print(c7, 3* sizeof(int));
check_memory();
memoryleak(c7);


int *c8= calloc(2,sizeof(int));
print(c8, 2* sizeof(int));
check_memory();
memoryleak(c8);


int *c9= calloc(8,sizeof(int));
print(c9, 8* sizeof(int));
check_memory();
memoryleak(c9);


int *c10= calloc(5,sizeof(int));
print(c10, 5* sizeof(int));
check_memory();
memoryleak(c10);



int *r1= realloc(m1,6* sizeof(int));
print(r1, 6* sizeof(int));
check_memory();
memoryleak(r1);


int *r2= realloc(m2,4* sizeof(int));
print(r2, 4* sizeof(int));
check_memory();
memoryleak(r2);


int *r3= realloc(m3,7* sizeof(int));
print(r3, 7* sizeof(int));
check_memory();
memoryleak(r3);


int *r4= realloc(m4,3* sizeof(int));
print(r4, 3* sizeof(int));
check_memory();
memoryleak(r4);


int *r5= realloc(m5,9* sizeof(int));
print(r5, 9* sizeof(int));
check_memory();
memoryleak(r5);


int *r6= realloc(m6,7* sizeof(int));
print(r6, 7* sizeof(int));
check_memory();
memoryleak(r6);


int *r7= realloc(m7,3* sizeof(int));
print(r7, 3* sizeof(int));
check_memory();
memoryleak(r7);


int *r8= realloc(m8,5* sizeof(int));
print(r8, 5* sizeof(int));
check_memory();
memoryleak(r8);


int *r9= realloc(m9,8* sizeof(int));
print(r9, 8* sizeof(int));
check_memory();
memoryleak(r9);


int *r10= realloc(m10,9* sizeof(int));
print(r10, 9* sizeof(int));
check_memory();
memoryleak(r10);



free(m1);
free(m2);
free(m3);
free(m4);
free(m5);
free(m6);
free(m7);
free(m8);
free(m9);
free(m10);


free(c1);
free(c2);
free(c3);
free(c4);
free(c5);
free(c6);
free(c7);
free(c8);
free(c9);
free(c10);

free(r1);
free(r2);
free(r3);
free(r4);
free(r5);
free(r6);
free(r7);
free(r8);
free(r9);
free(r10);


///////////////////////////////////////////////////////////////////////
//
// PART 3
// Using the new malloc to allocate memory with the ability to merge and 
// split.
///////////////////////////////////////////////////////////////////////


int *mf1= newmalloc(5* sizeof(int));
print(mf1, 5* sizeof(int));
check_memory();
memoryleak(mf1);


double *mf2= newmalloc(3* sizeof(double));
print(mf2, 3* sizeof(double));
check_memory();
memoryleak(mf2);


int *mf3= newmalloc(8* sizeof(int));
print(mf3, 8* sizeof(int));
check_memory();
memoryleak(mf3);


short *mf4= newmalloc(2* sizeof(short));
print(mf4, 2* sizeof(short));
check_memory();
memoryleak(mf4);


int *mf5= newmalloc(9* sizeof(int));
print(mf5, 9* sizeof(int));
check_memory();
memoryleak(mf5);


int *mf6= newmalloc(4* sizeof(int));
print(mf6, 4* sizeof(int));
check_memory();
memoryleak(mf6);


char *mf7= newmalloc(7* sizeof(char));
print(mf7, 7* sizeof(char));
check_memory();
memoryleak(mf7);


int *mf8= newmalloc(5* sizeof(int));
print(mf8, 5* sizeof(int));
check_memory();
memoryleak(mf8);


int *mf9= newmalloc(2* sizeof(int));
print(mf9, 2* sizeof(int));
check_memory();
memoryleak(mf9);


int *mf10= newmalloc(8* sizeof(int));
print(mf10, 8* sizeof(int));
check_memory();
memoryleak(mf10);

// printf("\n");
// printf(sbrk(0));
// printf("\n");
printf("sbrk(0) = %p\n", sbrk(0));


free(mf1);
free(mf2);
free(mf3);
free(mf4);
free(mf5);
free(mf6);
free(mf7);
free(mf8);
free(mf9);
free(mf10);



return 1;

}
