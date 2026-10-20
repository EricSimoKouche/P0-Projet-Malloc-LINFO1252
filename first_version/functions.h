#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stddef.h>
#include <stdint.h>

typedef struct Meta {
    uint32_t block_size;
    struct Meta* next;
} Meta_t;

void init(void);
void *my_malloc(size_t size);
void my_free(void *pointer);

#endif /* FUNCTIONS_H_*/