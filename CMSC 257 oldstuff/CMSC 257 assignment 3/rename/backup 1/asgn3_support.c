#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "asgn3_support.h"

/*************************************************************************
* Assignment 3 - Memory Management System
* CMSC 257 - Computer Systems
* Name - Liam Fernando 
*------------------------------------------------------------------------
**************************************************************************/

void *global_base = NULL;// head of the linked list. 


/**************************************************************************
* nofree_malloc()
* ------------------------------------------------------------------------
* Input		: size_t size
* Output	: p - pointer to available memory space thats free 
* Description	: Get more memory, ie. increase HEAP size, because there
* 	 	  is no other free memory blocks.
*
*************************************************************************/

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

/**************************************************************************
* find_free_block()
* ------------------------------------------------------------------------
* Input		: struct block_meta **last
* 		  size_t size
* Output	: current - block on the linked list thats free. 
* Description	: Find a free block in the linklist that is the right size 
* 		  for a request.  
*
**************************************************************************/



struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) { // 
    *last = current;
    current = current->next;
  }
  return current;
}


/**************************************************************************
* Struct request_space()
*--------------------------------------------------------------------------
*Input		: struct block_meta* last
		  size_t size 
*Output		: NULL if sbrk failed otherwise return block.
*Description	: Requesting memory block space.
*
**************************************************************************/

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); // Not thread safe.
 if (request == (void*) -1) {
    return NULL; // sbrk failed.
}

if (last) {  //NULL on first request.
last->next = block;
block->prev = last;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;
}


/**************************************************************************
* malloc()- Original 
*--------------------------------------------------------------------------
* Input		: size_t size
* Output	: On sueccess, returns the pointer to the beginning of newly 
* 		  allocated memory.
* Description	: Allocates size of uninitialized storage. 
*
***************************************************************************/

void *malloc(size_t size) {
  struct block_meta *block;


 if (size <= 0) {  // checking if size = 0 then return because there is no space for it to malloc
    return NULL;
  }

  if (!global_base) { // First call. 
    block = request_space(NULL, size); // if there is no head to the linked list then create one. 
    if (!block) {
      return NULL;
    }
    global_base = block; // otherwise make a head.
  }
 else 
{
    struct block_meta *last = global_base;  
    block = find_free_block(&last, size); // find the next free block.
    if (!block) { // Failed to find free block then request space because there was no free block.
      block = request_space(last, size);
      
      if (!block) {// if there is no space then dont do anything. 
	return NULL;
      }
    } else {   // found a free block 
      block->free = 0;  // free the block to be returned.  
      block->magic = 0x77777777;
    }
  }
  
  return(block+1);
}


/**************************************************************************
*  best_fit()- my edit
*--------------------------------------------------------------------------
* Input		: size_t size
* Output	: best fitted block
* Description	: looks for the best fit free block found in the linked list.
*
**************************************************************************/

struct block_meta *best_fit(size_t size)
{

  struct block_meta *current = global_base;
  struct block_meta *bestblock = NULL; // what our best block

  while (current){ // goes through entire list of block 
if (current->free && current->size >= size && (!bestblock || current->size < bestblock->size )) { // checks if the block free, determines if the block bigger than what is needed ( comparing the best block to use).
  bestblock= current; }
    current = current->next;
  }
  return bestblock;

}


/**************************************************************************
*  newmalloc()- my edit
*--------------------------------------------------------------------------
* Input		: size_t size
* Output	: On sueccess, returns the pointer to the beginning of newly
* 		  allocated memory.
* Description	: This version of malloc splits and merges blocks.
*
***************************************************************************/

void *newmalloc(size_t size) {
 

 struct block_meta *block;


 if (size <= 0) {  // checking if sise = 0 then return because there is no size
    return NULL;
  }

if (size%8 != 0){
size = ((size/8)*8)+8;

}

  if (!global_base) { // First call.
    block = request_space(NULL, size); // if there is no head to the linked list then create one.
    if (!block) {
      return NULL;
    }
    global_base = block; // otherwise make a head.
  }
 else
{
    struct block_meta *last = global_base;
    block = best_fit(size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);

      if (!block) {
        return NULL;
      }
    } else {
      split(block,size);
      block->free = 0;
      block->magic = 0x77777777;
      merge(block);
    }
  }

  return(block+1);
}



/**************************************************************************
* calloc()
*--------------------------------------------------------------------------
* Input		: size_t nelem
* 		  size_t elsize
* Output	: On success, returns the pointer to the beginning of newly
* 		  allocated memroy.
* Description	: Allocates memory for an array of num objects of the size
* 		  nelem and initalizes all bytes in the allocated storage 
* 		  to zero. 
*
***************************************************************************/

void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize;
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}


/**************************************************************************
* Struct get_block_ptr()
*-------------------------------------------------------------------------- 
* Input		: void *ptr
* Output	: block meta block 
* Description	: Converts the pointer type to a block meta type. 
**************************************************************************/

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}


/**************************************************************************
* free() - original 
*--------------------------------------------------------------------------
* Input		: void *ptr
* Output	: Nothing
* Description	: Frees the block at the selected pointer pointer memory
* 		  block.
* 
**************************************************************************/
 
void free(void *ptr) {
  if (!ptr||ptr==NULL) {
    return;
  } 

struct block_meta* block_ptr = get_block_ptr(ptr);
if(block_ptr==NULL||block_ptr->free)
return;
  assert(block_ptr->free == 0);
  assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->free = 1;
  block_ptr->magic = 0x55555555;
    

}


/**************************************************************************
* realloc()
*--------------------------------------------------------------------------
* Input		: void *ptr
* 		  size_t size
* Output	: On success, returns the pointer to the beginning of newly 
* 		  allocated memory.
* Description	: Reallocates the given area of memory. It must be previously
* 		  allocated and not yet freed.
* 
***************************************************************************/


void *realloc(void *ptr, size_t size) {
  if (!ptr) { // Null ptr. realloc should act like malloc. 
 return malloc(size);
  }


struct block_meta* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // We have enough space. Could free some once we implement split.
   return ptr;
         }
void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL;

 }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);  
  return new_ptr;
}


/**************************************************************************
* split()
*--------------------------------------------------------------------------
* Input		: struct block_meta* orig
* 		  size_t p_size
* Output	: Makes two new blocks
* Description	: The split resizes a block and makes a new block from the 
* 		  leftover memory.
*  
***************************************************************************/



void split(struct block_meta* orig, size_t p_size){

if (orig->size<=p_size){ // checks if what you need is bigger than what it has , it wont work.  
return;
}
struct block_meta *new= orig + p_size; // makes the new block, defines the start of the start
new->size=orig->size-p_size;   //sets the new block size by the original subtract the new size. 
new->free=1; // declares the split portion as free. 
new->magic= 0x55555555; // debugging 

orig->size=p_size;  // set old size to the new size
new->next=orig->next; // reroute the pointers
orig->next->prev=new; // reroute pointer of the third block.  
orig->next=new; // reroute the pointers 
new->prev=orig; //reroute the pointers

}


/**************************************************************************
* merge()
*--------------------------------------------------------------------------
* Input		: struct block_meta* start
* Output	: None
* Description	: Turns muliples free blocks into one big block. 
* 
***************************************************************************/


void merge(struct block_meta* start){

if(!start->free){// if the block im at is not free, dont merge it. 
return;
}
size_t new=start->size; // declare new size as the size of the first free block

struct block_meta *next= start->next;
while(next && next->free) // while there is a next free block merge them together
{
new += next->size;
next = next->next;

}

start->size=new; // start is now the size of the newly merged block. 
start->next= next; // set next to be the one after the newly merged block. 
next->prev=start; // set the pointer for unfree block.


}





















