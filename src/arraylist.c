#include "../include/arraylist.h"

array_list_t *array_list_create(usize item_size, usize initial_capacity) {
    array_list_t *list = (array_list_t*)malloc(sizeof(array_list_t));

    list->item_size = item_size;
    list->capacity = initial_capacity;
    list->lenght = 0;
    list->items = malloc(item_size * initial_capacity);
    
    if (!list->items)
        ERROR_RETURN(-1, "Failed to create item list");

    return list;
}

usize array_list_append(array_list_t *list, void *item) {
    if (list->lenght == list->capacity) {
        list->capacity = list->capacity > 0 ? (list->capacity * 2) : (1);
        void * items = realloc(list->items, (list->item_size * list->capacity));

        if (!items)
            ERROR_RETURN(-1, "Could not reallocate memory for Array List");
    }

    usize index = list->lenght++;
    memcpy(((u8*)list->items + (list->item_size * index)), item, list->item_size);
}

void *array_list_get(array_list_t *list, usize index) {
    if (index >= list->lenght)
        ERROR_RETURN(-1, "Index out of bounds");
        
    void *item = ((u8*)list->items + (list->item_size * index));
    return item;
}

u8 array_list_remove(array_list_t *list, usize index) {
    if (list->lenght == 0)
        ERROR_RETURN(-1, "List is empty");
    if (index >= list->lenght)
        ERROR_RETURN(-1, "Index out of bounds");
    if (list->lenght == 1) {
        list->lenght = 0;
        return 0;
    }

    --(list->lenght);

    u8 *item_ptr = (u8*)list->items + (list->item_size * index);
    u8 *end_ptr = (u8*)list->items + (list->lenght * list->item_size);

    memcpy(item_ptr, end_ptr, list->item_size);

    return 0;
}

void dbg_print_array_list(array_list_t *list, void (*print_func)(void *)) {
    u8 *list_ptr = (u8*)list->items;

    u8 item_bytes[list->item_size]; 

    for (int i = 0; i < list->lenght; i++) {
        memcpy(item_bytes, list_ptr, list->item_size);
        print_func(item_bytes);
        list_ptr += list->item_size;
    }
}