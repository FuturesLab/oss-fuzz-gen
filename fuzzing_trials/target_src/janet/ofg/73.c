#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

// Fuzzing harness for janet_tuple_head
int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure the size is sufficient to form a JanetTuple
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Calculate the number of elements that can fit into the size
    size_t num_elements = size / sizeof(Janet);

    // Allocate memory for the Janet elements
    Janet *elements = (Janet *)malloc(num_elements * sizeof(Janet));
    if (elements == NULL) {
        janet_deinit();
        return 0;
    }

    // Copy data into the allocated memory
    memcpy(elements, data, num_elements * sizeof(Janet));

    // Create a JanetTuple from the elements
    JanetTuple tuple = janet_tuple_n(elements, num_elements);

    // Check if the tuple is not empty before calling the function-under-test
    if (num_elements > 0) {
        // Call the function-under-test
        const Janet *result = janet_tuple_head(tuple);
        // Use result to avoid compiler optimizations (if needed)
        (void)result;
    }

    // Clean up
    free(elements);

    // Deinitialize the Janet environment
    janet_deinit();

    // Note: Janet tuples are immutable and do not require explicit cleanup
    return 0;
}