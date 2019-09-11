#ifndef A3SUPPORT_INCLUDED
#define A3SUPPORT_INCLUDED

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


struct block_meta {
  size_t size;    
  struct block_meta *next,*prev;  
  int free;  
  // int magic;
};


#define META_SIZE sizeof(struct block_meta) 

void *nofree_malloc(size_t size);

struct block_meta *find_free_block(struct block_meta **last,  size_t size);

struct block_meta *request_space(struct block_meta* last, size_t size);

void *malloc(size_t size);

void *calloc(size_t nelem, size_t elsize);

struct block_meta *get_block_ptr(void *ptr);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

/////////////
// void *malloc(size_t size);
// void *calloc(size_t nelem, size_t elsize);
// void *realloc(void *ptr, size_t size);
 ////////////

// void *nofree_malloc(size_t size);
// struct block_meta *find_free_block(struct block_meta **last, size_t size);
// struct block_meta *request_space(struct block_meta* last, size_t size);

// void merge (struct block_meta* start);
// void split ( struct block_meta* main, size_t p_size); 
// void *newmalloc(size_t size);
// struct block_meta *best_fit(size_t size);
// void newfree(void *ptr);




#endif



