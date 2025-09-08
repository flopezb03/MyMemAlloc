#include "../include/my_mem_alloc.h"

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>





typedef char ALIGN[16];

typedef union header_t{
    struct {
        size_t size;
        bool is_free;
        union header_t* next;
    }h;
    ALIGN stub;
}header_t;





header_t *head, *tail;
pthread_mutex_t global_malloc_lock;





header_t* get_free_block(size_t size);
void insert_header(header_t* new_header);





void* my_malloc(size_t size){
    if(size <= 0)
        return NULL;

    void* mem_block;
    header_t* header;

    pthread_mutex_lock(&global_malloc_lock);
    header = get_free_block(size);
    if(header != NULL){
        header->h.is_free = false;
        pthread_mutex_unlock(&global_malloc_lock);
        return (void *)(header+1);
    }

    mem_block = sbreak(sizeof(header_t)+size);
    if(mem_block == (void *)-1){
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL;
    }
    header = mem_block;
    header->h.size = size;
    header->h.is_free = false;
    insert_header(header);
    pthread_mutex_unlock(&global_malloc_lock);

    return (void *)(header+1);
}






header_t* get_free_block(size_t size){
    if(head == NULL)
        return NULL;

    header_t* out = head;
    while(out != NULL){
        if(out->h.is_free && out->h.size >= size)
            return out;
        out = out->h.next;
    }
    return NULL;
}

void insert_header(header_t* new_header){
    if(head == NULL)
        head = new_header;
    if(tail  != NULL)
        tail->h.next = new_header;
    tail = new_header;
}





void my_free(void* ptr){
    if(ptr == NULL)
        return;

    header_t* header = (header_t *) ptr;
    header = header-1;

    pthread_mutex_lock(&global_malloc_lock);

    if(header == tail){
        
        sbreak(-(sizeof(header_t)+header->h.size));

        if(header == head){
            head = NULL;
            tail = NULL;
        }else{
            header_t* it = head;
            bool found = false;
            while(!found){
                if(it->h.next == header)
                    found = true;
                else
                    it = it->h.next;
            }
            it->h.next = NULL
            tail = it;
        }
    }else{
        header->h.is_free = true;
    }
    pthread_mutex_unlock(&global_malloc_lock);
}

void* my_calloc(size_t nmemb, size_t size){
    if(nmemb <= 0 || size <= 0)
        return NULL

    size_t final_size = nmemb*size;
    void* block = my_malloc(final_size);
    if(block == NULL)
        return NULL
    memset(block,0,final_size);
    return block;
}