#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "/src/hoextdown/src/stack.h" // Correct path for hoedown_stack and hoedown_stack_grow

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize a hoedown_stack instance
    hoedown_stack stack;
    stack.item = (void **)malloc(sizeof(void *) * 10); // Initial allocation for items
    stack.size = 10; // Initial size
    stack.asize = 10; // Allocated size

    // Ensure the data size is non-zero for meaningful fuzzing
    if (size > 0) {
        // Use the first part of the data to determine the new size
        size_t new_size = (size_t)data[0]; // Use the first byte as the new size
        hoedown_stack_grow(&stack, new_size);
    }

    // Clean up
    free(stack.item);

    return 0;
}