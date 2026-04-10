#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/stack.h" // Correct path for hoedown_stack and hoedown_stack_pop

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Initialize a hoedown_stack object
    hoedown_stack stack;
    hoedown_stack_init(&stack, 4); // Initialize with a small size for testing

    // Push some elements onto the stack to ensure it is not empty
    if (size > 0) {
        for (size_t i = 0; i < size; ++i) {
            hoedown_stack_push(&stack, (void *)(uintptr_t)data[i]);
        }
    } else {
        // If size is 0, push at least one element to ensure the stack is not empty
        hoedown_stack_push(&stack, (void *)(uintptr_t)42);
    }

    // Call the function-under-test
    void *popped_element = hoedown_stack_pop(&stack);

    // Clean up
    hoedown_stack_uninit(&stack);

    return 0;
}