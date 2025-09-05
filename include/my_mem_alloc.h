#ifndef MY_MEM_ALLOC_H
#define MY_MEM_ALLOC_H

#include <stddef.h>

void* my_malloc(size_t size);
void free(void* ptr);
void* my_calloc(size_t nmemb, size_t size);
void* my_realloc(void *ptr, size_t size);


#endif