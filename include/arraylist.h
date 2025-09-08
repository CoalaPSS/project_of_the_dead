#pragma once

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "types.h"

#define MAX_CAPACITY 4194304 //4 MIB
#define DEFAULT_INITIAL_CAPACITY 1024

typedef struct _array_list {
    usize lenght;
    usize capacity;
    usize item_size;
    void *items;
} array_list_t;

array_list_t *array_list_create(usize item_size, usize initial_capacity);
usize array_list_append(array_list_t *list, void *item);
u8 array_list_remove(array_list_t *list, usize index);
void *array_list_get(array_list_t *list, usize index);

void dbg_print_array_list(array_list_t *list, void (*print_func)(void *));