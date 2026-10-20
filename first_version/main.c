#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

uint8_t MY_HEAP[64000];

void init() {
    Meta_t *first = (Meta_t *) MY_HEAP;
    first->block_size = sizeof(MY_HEAP);
    first->next = NULL;
}

void *my_malloc(size_t size) {
    Meta_t *first = (Meta_t *) MY_HEAP;

    Meta_t *current = first;
    while ( current != NULL &&
            ((current->block_size & 0x1) != 0 ||
            current->block_size <= size)) {
        current = current->next;
    }
    // J'ai atteint la fin la mémoire
    if (current == NULL) 
        return NULL;
    size_t newsize = size + sizeof(Meta_t);
    size_t oldsize = current->block_size & ~0x1;
    current->block_size = newsize | 0x1;
    if (newsize < oldsize)    


}

void my_free(void *pointer) {
    
}

void main(void) {

}
