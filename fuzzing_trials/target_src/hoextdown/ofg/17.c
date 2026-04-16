#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **item;
    size_t size;
    size_t asize;
} hoedown_stack;

void hoedown_stack_push(hoedown_stack *stack, void *item);

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize a hoedown_stack
    hoedown_stack stack;
    stack.size = 0;
    stack.asize = 16; // Initial arbitrary size
    stack.item = (void **)malloc(stack.asize * sizeof(void *));
    if (stack.item == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Iterate over each byte in the input data
    for (size_t i = 0; i < size; i++) {
        // Use each byte of data as an item to push onto the stack
        void *item = (void *)(data + i);

        // Call the function-under-test
        hoedown_stack_push(&stack, item);

        // Check if we need to resize the stack
        if (stack.size >= stack.asize) {
            stack.asize *= 2;
            stack.item = (void **)realloc(stack.item, stack.asize * sizeof(void *));
            if (stack.item == NULL) {
                return 0; // Exit if memory allocation fails
            }
        }
    }

    // Clean up
    free(stack.item);

    return 0;
}