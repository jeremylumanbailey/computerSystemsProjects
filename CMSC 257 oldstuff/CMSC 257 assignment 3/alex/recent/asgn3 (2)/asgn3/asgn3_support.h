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

struct block_meta *request_space(struct block_meta* last, size_t size);
void *malloc(size_t size);
struct block_meta *best_fit(size_t size);
void *calloc(size_t size1, size_t size2);
struct block_meta *get_block_ptr(void *ptr);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void split(struct block_meta* main, size_t p_size);
void merge(struct block_meta* start);
void *print_state(void *ptr, void *pt);
void total_memory_leak();
