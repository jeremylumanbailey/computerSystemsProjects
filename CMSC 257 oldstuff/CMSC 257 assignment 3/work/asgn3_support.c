#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "asgn3_support.h"


void *global_base = NULL;


/**************************************************************************


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

**************************************************************************/

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); 
 if (request == (void*) -1) {
    return NULL; 
}

if (last) {  
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

***************************************************************************/

void *malloc(size_t size) {
  struct block_meta *block;


 if (size <= 0) {  
    return NULL;
  }

  if (!global_base) {
    block = request_space(NULL, size); 
    if (!block) {
      return NULL;
    }
    global_base = block;
  }
 else 
{
    struct block_meta *last = global_base;  
    block = find_free_block(&last, size); 
    if (!block) { 
      block = request_space(last, size);
      
      if (!block) {
	return NULL;
      }
    } else {  
      block->free = 0; 
      block->magic = 0x77777777;
    }
  }
  
  return(block+1);
}


/**************************************************************************

**************************************************************************/

struct block_meta *best_fit(size_t size)
{

  struct block_meta *current = global_base;
  struct block_meta *bestblock = NULL; 

  while (current){  
if (current->free && current->size >= size && (!bestblock || current->size < bestblock->size )) { 
  bestblock= current; }
    current = current->next;
  }
  return bestblock;

}


/**************************************************************************

***************************************************************************/

void *newmalloc(size_t size) {
 

 struct block_meta *block;


 if (size <= 0) {  
    return NULL;
  }

if (size%8 != 0){
size = ((size/8)*8)+8;

}

  if (!global_base) { 
    block = request_space(NULL, size); 
    if (!block) {
      return NULL;
    }
    global_base = block; 
  }
 else
{
    struct block_meta *last = global_base;
    block = best_fit(size);
    if (!block) { 
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

***************************************************************************/

void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize;
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}


/**************************************************************************

**************************************************************************/

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}


/**************************************************************************

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

***************************************************************************/


void *realloc(void *ptr, size_t size) {
  if (!ptr) { 
 return malloc(size);
  }


struct block_meta* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    
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

***************************************************************************/



void split(struct block_meta* orig, size_t p_size){

if (orig->size<=p_size){ 
return;
}
struct block_meta *new= orig + p_size; 
new->size=orig->size-p_size;   
new->free=1; 
new->magic= 0x55555555;  

orig->size=p_size;  
new->next=orig->next; 
orig->next->prev=new; 
orig->next=new; 
new->prev=orig; 

}


/**************************************************************************

***************************************************************************/


void merge(struct block_meta* start){

if(!start->free){
return;
}
size_t new=start->size; 

struct block_meta *next= start->next;
while(next && next->free) 
{
new += next->size;
next = next->next;

}

start->size=new; 
start->next= next;
next->prev=start; 


}





















