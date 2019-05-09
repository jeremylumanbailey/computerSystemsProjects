//////////////////////////////////////////////////////////////////////////////
//
//  File          : asgn3_support.c
//  Description   : This is the support file for the functions for assignment
//                  3 of the CMSC257 course.
//
//
//
//  Author        : Jeremy Bailey
//  Created       : March 2019

// Include Files
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include "asgn3_support.h"

void *global_base = NULL;

// Function Implementations

//His functions

void *nofree_malloc(size_t size) {
  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) { 
    return NULL; // sbrk failed
  } else {
    assert(p == request); // Not thread safe.
    return p;
  }
}


struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

/******************************************************************
 *  request_space
 * ***************************************************************/

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); // Not thread safe.
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }
  
  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;
}
/******************************************************************
 *  malloc
 * ***************************************************************/
void *malloc(size_t size) {
  struct block_meta *block;
  // TODO: align size?

  if (size <= 0) {
    return NULL;
  }

  if (!global_base) { // First call.
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block) {
	return NULL;
      }
    } else {      // Found free block
      // TODO: consider splitting block here.
      block->free = 0;
      block->magic = 0x77777777;
    }
  }
  
  return(block+1);
}














//My functions

/*
#-----------------------------------------------------------------------------------------------------------------------#
# *malloc Allocates a segment of memory in the heap, of at least the given size,
# and return a point to this segment.
#
# Input -
# Output -
#-----------------------------------------------------------------------------------------------------------------------#
*/
    void *malloc(size_t size) 
{



}

/*
#-----------------------------------------------------------------------------------------------------------------------#
# *calloc() Allocate a segment of memory in the heap to store nitems elements of the given size.
# Set the entire segment of memory to 0. Return a point to this segment.
# 
#
# Input -
# Output -
#-----------------------------------------------------------------------------------------------------------------------#
*/
    void *calloc(size_t nitems, size_t size) 
{



}

/*
#-----------------------------------------------------------------------------------------------------------------------#
# *realloc - Resize the memory segment pointed to by ptr to the give size.
# Return the pointer to the newly sized segment.
#
#
# Input -
# Output -
#-----------------------------------------------------------------------------------------------------------------------#
*/  
    void *realloc(void *ptr, size_t size)
{


}
 
/*
#-----------------------------------------------------------------------------------------------------------------------#
# free() - Deallocated the memory segment pointed to by ptr.
# 
#
# Input -
# Output -
#-----------------------------------------------------------------------------------------------------------------------#
*/
    void free(void *ptr)
{


}



void Hello(int x) {

        printf("Hello world");

}




