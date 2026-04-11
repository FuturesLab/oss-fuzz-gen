#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <assert.h>
#include "/src/hoextdown/src/stack.h"

#define MAX_INITIAL_SIZE 1024  // Define a reasonable maximum size for initial_size

static void initialize_stack(hoedown_stack *st, size_t initial_size) {
    hoedown_stack_init(st, initial_size);
}

static void cleanup_stack(hoedown_stack *st) {
    hoedown_stack_uninit(st);
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return 0;

    size_t initial_size = *((size_t *)Data);
    if (initial_size > MAX_INITIAL_SIZE) return 0;  // Check and limit initial_size

    Data += sizeof(size_t);
    Size -= sizeof(size_t);

    hoedown_stack stack;
    initialize_stack(&stack, initial_size);

    for (size_t i = 0; i < Size; ++i) {
        hoedown_stack_push(&stack, (void *)(uintptr_t)Data[i]);
    }

    if (stack.size > 0) {
        void *top_item = hoedown_stack_top(&stack);
        void *popped_item = hoedown_stack_pop(&stack);
        assert(top_item == popped_item);
    }

    cleanup_stack(&stack);

    return 0;
}