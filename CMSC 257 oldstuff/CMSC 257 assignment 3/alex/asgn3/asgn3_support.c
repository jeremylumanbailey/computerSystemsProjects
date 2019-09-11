#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "asgn3_support.h"

//**************************************
//
//Jorge Alex Villavicencio
//For CMSC257 Assignment 3
//
//Support file contans functionality for the following functions:
//void *malloc(size_t size)
//void *calloc(size_t nitems, size_t size)
//void *realloc(void *ptr, size_t size)
//void free(void *ptr)
//
//**************************************

struct block_meta {
      struct block_meta *next, *previous; // Pointers to next and previous blocks in doubly-linked list form
      size_t size; //total size of block
      int free; //total unallocated amount of block size
};

#define META_SIZE sizeof(struct block_meta) //size of the meta block struct




void *meta_head = NULL; //head of meta block linked list

//********************************
//Name: nofree_malloc()
//Description:
//
//Input:
//Output: 
//Uses: sbrk
//
//********************************
//void *nofree_malloc(size_t size){
//	void *p = sbrk(0);
//	void *request = sbrk(size);
//	if (request == (void*) -1){//Check uf sbrk failed, return null if so
//		return NULL;
//	} else{
//		return p;
//	}
//}

//********************************
//Name: find_free_blok()
//Description:
//
//Input:
//Output:
//
//********************************
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
	struct block_meta *current = meta_head;
	while (current && !(current->free && current->size == size)) {
		*last = current;
		current->previous = current;
		current = current->next;
	}
	return current;
}

//********************************
//Name: request_space()
//Description:
//
//Input:
//Output:
//
//********************************
struct block_meta *request_space(struct block_meta* last, size_t size) {
	struct block_meta *block;
	block = sbrk(0);
	void *request = sbrk(size + META_SIZE);
	if (request == (void*) -1){ //In case sbrk fails, return NULL
		return NULL; 
	}
	if (last) {
	last->next = block;
	block->previous = last;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}

//********************************
//Name: 
//Description:
//
//Input:
//Output:
//
//********************************

void *malloc(size_t size) {
	struct block_meta *block;
	if(size <= 0) { //Check for case that the provided size is invalid, return null in such case.
		return NULL;
	}
	if (size%8 !=0){
	size = (size+(8-(size%8)));
	}
	if(meta_head==NULL){
		block = request_space(NULL, size); 
		if(!block) {
			return NULL;
		}
		meta_head = block;
	} else{
		struct block_meta *last = meta_head;
		block = best_fit(size);
		if(!block) {
			block = request_space(last, size);
			if(!block){
				return NULL;
			} else {
				split(block, size);
				block->free =0;
				merge(block);
			}
		}
	}
return (block+1);
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
struct block_meta *best_fit(size_t size){
	struct block_meta *current = meta_head;
	struct block_meta *bestblock = NULL; 

	while(current){
		if(current->free && current->size >=size && (!bestblock || current->size < bestblock->size)){
		bestblock = current;
		current = current->next;
		}	
	}
	return bestblock;
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
void *calloc(size_t size1, size_t size2) {
	size_t size = size1 * size2;
	void *ptr = malloc(size);
	memset(ptr, 0, size);
	return ptr;
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
struct block_meta *get_block_ptr(void *ptr) {
	return (struct block_meta*)ptr - 1;
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
void free(void *ptr){
	if (!ptr||ptr==NULL){
		return;
	}
	struct block_meta* block_ptr = get_block_ptr(ptr);
	if(block_ptr==NULL||block_ptr->free) {
		return;
	}
	block_ptr->free = 1;
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
void *realloc(void *ptr, size_t size) {
	if(ptr==NULL){
		return malloc(size);
	}
	struct block_meta* block_ptr = get_block_ptr(ptr);
		if(block_ptr->size >=size){
			return ptr;
		}
	void *new_ptr;
	new_ptr = malloc(size);
	if (new_ptr) {
		return NULL;
	}
	memcpy(new_ptr, ptr, block_ptr->size);
	free(ptr);
	return new_ptr;	
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
void split(struct block_meta* orig, size_t p_size){
	if (orig->size%8!=0){
		orig->size = (orig->size+(8-(orig->size%8)));
	}
	if (orig->size<=p_size){
		return;
	}
	struct block_meta *new = orig + p_size;
	new->size=orig->size - p_size;
	new->free = 1;
	orig->size=p_size;
	new->next=orig->next;
	orig->next->previous=new;
	orig->next=new;
	new->previous=orig;
}

//********************************
//Name:
//Description:
//
//Input:
//Output:
//
//********************************
void merge(struct block_meta* start){
	if(!start->free){
		return;
	}
	size_t new = start->size;
	struct block_meta *next = start->next;
	while(next && next->free) {
		new += next->size;
		next = next->next;
	}
	start->size = new;
	start->next = next;
	next->previous = start;
}
