#include <assert.h>
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

if(!first->free){// if the block im at is not free, dont merge it. 
return;
}
size_t new=first->size; // declare new size as the size of the first free block

struct block_meta *next= first->next;
while(next && next->free) // while there is a next free block merge them together
{
new += next->size;
next = next->next;

}

first->size = new; // start is now the size of the newly merged block. 
first->next = next; // set next to be the one after the newly merged block. 
next->prev = first; // set the pointer for unfree block.


}

//////////////////////////////////////////////////////////////////////////
//
//  split() takes a block and cuts it into two blocks from the unused
//  free memory in the original block
//
//  Input - first, 
//
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

//////////////////////////////////////////////////////////////
//
//  nofree_malloc() mallocates memory for the heap if there is no
//  free memory already availible
//
//  Input - size
//
//  Output - p (pointer to free memory)
//
//////////////////////////////////////////////////////////////

void *nofree_malloc(size_t size) {
  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) { 
    return NULL; // sbrk failed
  } else {
 //   assert(p == request); // Not thread safe.
    return p;
  }
}

/////////////////////////////////////////////////////////////
//
//  find_free_block() finds a best fit block in the linkedlist that is 
//  big enough for the size required
//
//  Input - block_meta, **last, size
//
//  Output - current
//
/////////////////////////////////////////////////////////////
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



// //FROM MALLOC.C i think this is basically 'first fit'
// struct block_meta *find_free_block(struct block_meta **last, size_t size) {
//   struct block_meta *current = global_base;
//   while (current && !(current->free && current->size >= size)) {
//     *last = current;
//     current = current->next;
//   }
//   return current;
// }

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


//FROM MALLOC.C
// If it's the first ever call, i.e., global_base == NULL, request_space and set global_base.
// Otherwise, if we can find a free block, use it.
// If not, request_space.
///////////////////////////////////////////////////////////////////////////////////////////
//
//  malloc() allocates size of unitialized using split and merge as well as
//  making sure the size is a multiple of 8
//
//  Input - size
//
//  Output - NULL or (block + 1)
//
//////////////////////////////////////////////////////////////////////////////////////////
void *malloc(size_t size) {
  struct block_meta *block;


 if (size <= 0) {  // checking if sise = 0 then return because there is no size
    return NULL;
  }

if (size % 8 != 0){
size = (8 - (size % 8)) ;

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
  // struct block_meta *find_free_block(struct block_meta **last, size_t size)
    struct block_meta *last = global_base;
    block = find_free_block(last, size);
    // block = best_fit(size);
    // if (!block) { // Failed to find free block.
    //   block = request_space(last, size);

    //   if (!block) {
    //     return NULL;
    //   }
    // } else {
      split(block,size);
      block->free = 0;
 
      merge(block);
  //  }
  }

  return(block+1);
}
///////////////////////////////////////////////////////////////////////////
//
//  *malloc() Allocates size of unitialized storage
//
//  Input - size
//
//  Output - NULL or (block + 1) 
//
///////////////////////////////////////////////////////////////////////////
//ORIGINAL
// void *malloc(size_t size) {
//   struct block_meta *block;
//   // TODO: align size?

//   if (size <= 0) {
//     return NULL;
//   }

//   if (!global_base) { // First call.
//     block = request_space(NULL, size);
//     if (!block) {
//       return NULL;
//     }
//     global_base = block;
//   } else {
//     struct block_meta *last = global_base;
//     block = find_free_block(&last, size);
//     if (!block) { // Failed to find free block.
//       block = request_space(last, size);
//       if (!block) {
//   return NULL;
//       }
//     } else {      // Found free block
//       // TODO: consider splitting block here.
//       block->free = 0;
//       // block->magic = 0x77777777;
//     }
//   }
  
//   return(block+1);
// }

//FROM MALLOC.C
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


//FROM MALLOC.C
// TODO: maybe do some validation here.
////////////////////////////////////////////////////////////
//
//  *get_block_ptr() is used to assis in getting the 
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


//FROM MALLOC.C
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

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta* block_ptr = get_block_ptr(ptr);
  if(block_ptr == NULL || block_ptr->free) {
    return;
  }
  // assert(block_ptr->free == 0);
  // assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->free = 1;
 // block_ptr->magic = 0x55555555;  
}



//FROM MALLOC.C
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
    return NULL; // TODO: set errno on failure.
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);  
  return new_ptr;
}

