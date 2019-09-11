#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "asgn3_support.h"

//**************************************
//Jorge Alex Villavicencio
//For CMSC257 Assignment 3
//
//Support file contans functionality for the following functions:
//void *malloc(size_t size)
//void *calloc(size_t nitems, size_t size)
//void *realloc(void *ptr, size_t size)
//void free(void *ptr)
//
//Support functions:
//struct block_meta *best_fit(size_t size)
//void split(struct block_meta* orig, size_t p_size)
//void merge(struct block_meta* start)
//struct block_meta *get_block_ptr(void *ptr)
//void *print_state(void *ptr, void *pt)
//void total_memory_leakage()
//**************************************

struct block_meta {
      struct block_meta *next, *previous; // Pointers to next and previous blocks in doubly-linked list form
      size_t size; //total size of block
      int free; //total unallocated amount of block size
};

#define META_SIZE sizeof(struct block_meta) //size of the meta block struct


void *meta_head = NULL; //head of meta block linked list


//********************************
//Name: request_space()
//Description: Creates a meta block for a given size and previous node.
//
//Input: Pointer to a previous meta block and a size to be allocated.
//Output: Pointer to an allocated meta block.
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
	block->free = block->size-size;
	return block;
}

//********************************
//Name: malloc
//Description: Allocate meta block to accomodate a given size as a multiple of 8.
//
//Input: Size to be allocated.
//Output: Pointer to an allocated meta block.
//
//********************************

void *malloc(size_t size) {
	struct block_meta *block;
	if(size <= 0) { //Check for case that the provided size is invalid, return null in such case.
		return NULL;
	}
	size_t newsize = size;
	if (newsize%8 !=0){ //Check if space to be allocated for process is a multiple of 8 and fix it if needed.
	newsize = (newsize+(8-(newsize%8)));
	}
	if(meta_head==NULL){ //Check if head of list is null.
		block = request_space(NULL, newsize); 
		if(!block) {
			return NULL;
		}
		meta_head = block;
	} else{ //Otherwise search through list and allocate where appropriate
		block = best_fit(newsize);
		if(block==NULL) {
			return NULL;
		}
	}
	block->free = block->size-size;
	return (block+1);
}

//********************************
//Name: best_fit
//Description: Finds the best-fitting available memory location and calls request_space function if no appropriate meta blocks are available for allocation.
//
//Input: size of block to be allocated.
//Output: allocated meta block.
//
//********************************
struct block_meta *best_fit(size_t size){
	struct block_meta *current = meta_head;
	struct block_meta *bestblock = NULL;
	struct block_meta *prevblock = meta_head;

	while(current){ //Iterate through list to find appropriate block
		if(current->free==current->size){ //Check if block is unallocated
			if(current->size >=size && (!bestblock || current->size < bestblock->size)){ //Allocate the block if it is appropriate to accomodate the given size
				bestblock = current;
			}else{ //Check if there is a block to merge with, if not.
				merge(current);
			}
		}	
		prevblock = current;
		current = current->next;
	}
	if (bestblock==NULL){ //Create block at end of linked list if no appropriate are found
		bestblock = request_space(prevblock, size);
	} else{
		if (bestblock->size>=(2*size)){ //If given block is twice or more than the size of the needed size, split into smaller blocks.
			split(bestblock, size);
		}
	}
	return bestblock;
}

//********************************
//Name: calloc
//Description: Allocates memory block, given two size values and sets the value of each allocated memory location to 0.
//
//Input: two size values to be used to calculate the full amount of memory to be allocated.
//Output: allocated and initialized meta block.
//
//********************************
void *calloc(size_t size1, size_t size2) {
	size_t size = size1 * size2; //Calculate size needed for meta block, then allocate
	void *ptr = malloc(size);
	memset(ptr, 0, size); //Initialize memory and return
	return ptr;
}

//********************************
//Name: get_block_ptr
//Description: Returns the pointer to prevous block meta struct.
//
//Input: pointer to current meta block
//Output: pointer to previous meta block
//
//********************************
struct block_meta *get_block_ptr(void *ptr) {
	return (struct block_meta*)ptr - 1;
}

//********************************
//Name: free 
//Description: De-allocates a block of memory and set the free space equal to its size.
//
//Input: pointer to block of memory to be de-allocated.
//Output: void
//
//********************************
void free(void *ptr){
	if (ptr==NULL){ //If the given pointer is null, return
		return;
	}
	struct block_meta* block_ptr = get_block_ptr(ptr);
	if(block_ptr==NULL||block_ptr->free==block_ptr->size) { //Check if memory block is already unallocated
		return;
	}
	block_ptr->free = block_ptr->size;
}

//********************************
//Name: realloc
//Description: Re-allocates memory to a given meta block struct
//
//Input: A pointer to a meta block struct to have its memory re-allocated and the size of the space to be re-allocated to it 
//Output: a re-allocated block of memory
//
//********************************
void *realloc(void *ptr, size_t size) {
	if(ptr==NULL){ //If the given pointer is null, allocate meta block
		return malloc(size);
	}
	struct block_meta* block_ptr = get_block_ptr(ptr);
		if(block_ptr->size >=size){ //If the size of the struct is already big enough, return the current pointer unchanged.
			return ptr;
		}
	void *new_ptr;
	new_ptr = malloc(size);
	if (new_ptr==NULL) { //If cound not allocate the memory, return null
		return NULL;
	}
	memcpy(new_ptr, ptr, block_ptr->size); //Copy memory and de-reference old block
	free(ptr);
	return new_ptr;	
}

//********************************
//Name: split
//Description: Takes a given free block meta struct and splits off a smaller section from it.
//
//Input: A block meta struct to be split and the size of the section to be split off from it.
//Output: void
//
//********************************
void split(struct block_meta* orig, size_t p_size){
	if (orig->size%8!=0){ //Checks to ensure that the size is a multiple of 8
		orig->size = (orig->size+(8-(orig->size%8)));
	}
	if (orig->size<=p_size){ //Catches if the size is too big to split the given node
		return;
	}
	struct block_meta *new = orig + p_size; //split node
	new->size=orig->size - p_size;
	new->free = p_size-META_SIZE;
	orig->size=p_size;
	new->next=orig->next;
	orig->next->previous=new;
	orig->next=new;
	new->previous=orig;
}

//********************************
//Name: merge
//Description: merges a free block with the next free block.
//
//Input: A starting block meta struct.
//Output: void
//
//********************************
void merge(struct block_meta* start){
	if(start->free!=start->size){ //Check if the given block is already allocated
		return;
	}
	size_t new = start->size;
	struct block_meta *nextnode = start->next;
	while(nextnode) {
		if(nextnode->free==nextnode->size){ //If an unallocated node is found, merge the starting node with the current and remove first old node
		new += nextnode->size;
		nextnode->size = new;	
		nextnode->free = new;

		start->previous->next = start->next; //De-reference old node
		start->previous->next->previous = start->previous;
		
		return;
		}
		nextnode = nextnode->next;
	}
	return;
}

//********************************
//Name: print_state
//Description: prints the current state of a given pointer, the memory leakage of the process, the current location of the heap, and the previous location of the heap. 
//
//
//Input: void pointer of the given node and the void pointer of the previous heap location.
//Output: void pointer of the current heap location.
//
//********************************
void *print_state(void *ptr, void *pt) {

	struct block_meta *block = get_block_ptr(ptr);	

	if(block->size==block->free){
		printf("Start of Space: %p is free\n", ptr);
		return(pt);
	}
	

        printf("Start of Space: %p\n", ptr);
        printf("End of Space:   %p\n", ptr + block->size);

      int leakage = 0;

	printf("Total Size:     %d\n",(int) block->size);

      leakage = block->free;
      printf("Memory Leakage:   %d\n", leakage);

        void *pt1 = sbrk(0);

        printf("Current Heap Location: %p, Previous: %p\n", pt, pt1);
        return (pt1);
}

//********************************
//Name: total_memory_leakage
//Description: traverses the linked list of memory blocks, adding up any free values inside of each block and displaying at the end.
//
//Input: none
//Output: void
//
//********************************
void total_memory_leakage(){
	struct block_meta *head = meta_head;
	int i = 0;
	while(head!=NULL){
		if(head->free!=head->size){
			i = (i+head->free);
		}
		head = head->next;
	}
	printf("Total Memory Leakage: %d\n", i); 
}
