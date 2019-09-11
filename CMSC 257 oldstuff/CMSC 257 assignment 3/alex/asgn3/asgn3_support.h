#ifndef ASGN3_SUPPORT_INCLUDED
#define ASGN3_SUPPORT_INCLUDED

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//***********************************
//
//Jorge Alex VIllavicencio
//for CMSC 257 Assignment 3
//
//
//***********************************

//struct block_meta {
//	struct block_meta *next, *previous; // Pointers to next and previous blocks in doubly-linked list form 
//	size_t size; //total size of block
//	int free; //total unallocated amount of block size
//};

//#define META_SIZE sizeof(struct block_meta) //size of the meta block struct



void *nofree_malloc(size_t size);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
//struct block_meta *request_space(struct block_meta* last, size_t size);
void *malloc(size_t size);
void *calloc(size_t size1, size_t size2);
struct block_meta *get_block_ptr(void *ptr);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void merge(struct block_meta* start);
void split(struct block_meta* main, size_t p_size);
struct block_meta *best_fit(size_t size);
void newfree(void *ptr);

#endif
