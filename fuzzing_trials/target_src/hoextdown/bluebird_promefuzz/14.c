#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/hoextdown/src/stack.h"

static void initialize_stack(hoedown_stack *st, size_t initial_size) {
    hoedown_stack_init(st, initial_size > 0 ? initial_size : 8); // Ensure initial size is at least 8
}

static void push_items_to_stack(hoedown_stack *st, size_t num_items) {
    for (size_t i = 0; i < num_items; i++) {
        void *item = malloc(sizeof(int)); // Example item, replace with appropriate data
        if (item) {
            *(int *)item = i; // Assign some value
            hoedown_stack_push(st, item);
        }
    }
}

static void cleanup_stack(hoedown_stack *st) {
    while (hoedown_stack_top(st) != NULL) {
        free(hoedown_stack_pop(st));
    }
    hoedown_stack_uninit(st);
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return 0;

    hoedown_stack stack;
    size_t initial_size = *((size_t *)Data) % 1024; // Limit the initial size to avoid excessive allocation
    Data += sizeof(size_t);
    Size -= sizeof(size_t);

    initialize_stack(&stack, initial_size);

    if (Size > 0) {
        size_t num_items = *Data % 10; // Limit number of items to push
        push_items_to_stack(&stack, num_items);
    }

    void *top_item = hoedown_stack_top(&stack);
    if (top_item) {
        // Optionally do something with the top item
    }

    hoedown_stack_grow(&stack, initial_size + 10); // Example grow usage

    cleanup_stack(&stack);

    return 0;
}