#include "stdio.h"
// Project Includes
#include "asgn3_support.h"

//////////////////////////////////////////////////////////////////
void memleak(void *ptr){

int leak = 0;

struct block_meta *block = get_block_ptr(ptr);

if ( block->size < META_SIZE) {
leak+=(META_SIZE-block->size);
}

if ( block->free){

leak+=block->size;

}

printf ("memroy leak is: %d\n", leak);


}


/////////////////////////////////////////////////////////////////
void printMaAddress( void *ptr, int size )
{
	printf("Start Address: %p\n",ptr);
	printf("End Address  : %p\n", ptr + size);
	memleak(ptr);
	printf("%s\n","----------------------------");
}

int main( ) {
printf("%s\n","----------------------------");

int *test1= malloc(5* sizeof(int));
printMaAddress(test1,  sizeof(int));



// char *test2= malloc(sizeof(char));
// printMaAddress(test2,  sizeof(char));

// double *test3= malloc(sizeof(double));
// printMaAddress(test3, sizeof(double));
printf("%ld\n",sizeof(struct block_meta));
	
	printf("%ld\n",sizeof(size_t));

	printf("%ld\n",sizeof(META_SIZE));

    printf("%ld\n",sizeof(int));
    printf("%ld\n",sizeof(char));  
    printf("%ld\n",sizeof(float)); 
    printf("%ld\n",sizeof(double)); 

printf("%s\n","asgn3 main ran" );
return 0;

}
