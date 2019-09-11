#ifndef A3SUPPORT_INCLUDED
#define A3SUPPORT_INCLUDED

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*************************************************************************
 * * Assignment 3 - Memory Management System
 * * CMSC 257 - Computer Systems
 * *------------------------------------------------------------------------
 * **************************************************************************/

/****************************************************************************
 * Struct block_meta
 *---------------------------------------------------------------------------
 * Input	:NONE
 * Output	:NONE
 * Description  :block structure
 * *
 ***************************************************************************/

struct block_meta {
  size_t size;    
  struct block_meta *next,*prev;  //  Pointer to next data block -- NULL indicates end of linked list // Pointer to preve data block --
  int free;  
  int magic;
};


#define META_SIZE sizeof(struct block_meta) // size of the block structure. 

void *malloc(size_t size);
void *calloc(size_t nelem, size_t elsize);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

void *nofree_malloc(size_t size);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
struct block_meta *get_block_ptr(void *ptr);
void merge (struct block_meta* start);
void split ( struct block_meta* main, size_t p_size); 
void *newmalloc(size_t size);
struct block_meta *best_fit(size_t size);
void newfree(void *ptr);




#endif



