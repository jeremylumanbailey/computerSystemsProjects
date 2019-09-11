#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <asgn3_support.h>

///////////////////////////////////////////////////////////////
//
//  Author: Jeremy Bailey
//  March 2019
//  CMSC 257 Assignment 3
//
///////////////////////////////////////////////////////////////

//Head node
void *global_base = NULL;

///////////////////////////////////////////////////////////////
//
//  merge() combines adjacent free blocks into one
//
//  Input - first
//
//  Output - none (adjusts pointers)
//
///////////////////////////////////////////////////////////////

void merge(struct block_meta* first){

if(!first->free){ //if free is false, don't try to merge
return;
}
size_t newBlock = first->size; // set newBlock to first's size

struct block_meta *next= first->next;
while(next && next->free) // continue merging as long adjacent blocks are free
{
newBlock += next->size; 
next = next->next;

}

first->size = newBlock; // set first's size to newBlock
first->next = next; // set first's pointer to correct next block in link
next->prev = first; // set the next block in the chain's prev to point to first

}

//////////////////////////////////////////////////////////////////////////
//
//  split() takes a block and cuts it into two blocks from the unused
//  free memory in the original block
//
//  Input - first, sizeNeed
//
//  Output - nothing (splits an existing block)
//
//////////////////////////////////////////////////////////////////////////
void split(struct block_meta* first, size_t sizeNeed){

if (first->size<=sizeNeed){ //Make sure enough supply for demand
return;
}
struct block_meta *newBlock= first + sizeNeed; // Create newBlock and points to it
newBlock->size=first->size-sizeNeed;   //Set newBlock size to first minus sizeNeed
newBlock->free=1; //Set newBlock's to free to 1 (true)

first->size=sizeNeed;  // Set old size to sizeNeed
newBlock->next=first->next; // Correct newBlock's next pointer
first->next->prev=newBlock; // Correct first's prev pointer  
first->next=newBlock; // Correct first's next pointer
newBlock->prev=first; // Correct newBlock's prev pointer

}

/////////////////////////////////////////////////////////////////////////
//
//  find_free_block() finds a best fit block in the linkedlist that is 
//  big enough for the size required
//
//  Input - block_meta, **last, size
//
//  Output - current
//
//////////////////////////////////////////////////////////////////////////
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  struct block_meta *bestFit = NULL;
  struct block_meta *previous = global_base;
  
  while (current) {
    if(current->free && current->size >= size && (!bestFit || current->size < bestFit->size)) {
      bestFit = current; 
      
    }
    previous = current;
    current = current->next;
  }
if(!bestFit) {
  bestFit = request_space(previous, size);
}

  return bestFit;
}

////////////////////////////////////////////////////////////////////////
//
//  request_space() requests space from the OS using sbrk
//
//  Input - block_meta* last, size
//
//  Output - NULL or block
//
////////////////////////////////////////////////////////////////////////
struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);

  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }
  
  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  malloc() allocates size of unitialized using split and merge as well as
//  making sure the size is a multiple of 8.
//  If it's the first ever call, i.e., global_base == NULL, request_space and set global_base.
//  Otherwise, if we can find a free block, use it. If not, request_space.
//  Input - size
//
//  Output - NULL or (block + 1)
//
//////////////////////////////////////////////////////////////////////////////////////////
void *malloc(size_t size) {
  struct block_meta *block;


 if (!size) {  // if size is set to 0: return NULL
    return NULL;
  }

if (size % 8 != 0){
size = (8 - (size % 8));
}

  if (!global_base) { // Create head of linked list if head is NULL
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block; // otherwise make a head.
  }
 else
{

    struct block_meta **last = global_base;
    block = find_free_block(last, size);
 
      split(block,size);
      block->free = 0;
 
      merge(block);
  }

  return(block+1);
}

////////////////////////////////////////////////////////////////////
//
//  calloc() clears memory before returning a point
//
//  Input - nelem, elsize
//
//  Output - ptr
//
///////////////////////////////////////////////////////////////////
void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize;
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}

////////////////////////////////////////////////////////////
//
//  *get_block_ptr() is used to assist in getting the 
//    address of our struct in multiple places
//
//  Input - ptr
//
//  Output - (struct block_meta*)ptr -1
//  
/////////////////////////////////////////////////////////////
struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

//////////////////////////////////////////////////////////////////
//
//  free() frees the memory block wherever the pointer points to
//
//  Input - ptr
//
//  Output - returns nothing if block is already free, or frees it
//
//
//////////////////////////////////////////////////////////////////
void free(void *ptr) {
  if (!ptr) {
    return;
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);
  if(block_ptr == NULL || block_ptr->free) {
    return;
  }
  block_ptr->free = 1;  
}

/////////////////////////////////////////////////////////////////////
//
//  *realloc() reallocates the memory given to it if the memory is 
//  allocated but not freed.
//
//  Input - ptr, size
//
//  Output - malloc(size), ptr, NULL, new_ptr
//
/////////////////////////////////////////////////////////////////////
void *realloc(void *ptr, size_t size) {
  if (!ptr) { 
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // We have enough space. Could free some once we implement split.
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL; 
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);  
  return new_ptr;
}

