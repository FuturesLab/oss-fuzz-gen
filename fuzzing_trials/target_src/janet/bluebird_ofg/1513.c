#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1513(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Ensure the size is sufficient to create at least one Janet element
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Calculate the number of Janet elements we can create
    int32_t num_elements = size / sizeof(Janet);

    // Allocate memory for Janet elements
    Janet *janet_elements = (Janet *)malloc(num_elements * sizeof(Janet));
    if (janet_elements == NULL) {
        janet_deinit();
        return 0;
    }

    // Copy data into Janet elements
    for (int32_t i = 0; i < num_elements; i++) {
        // Safely copy data into Janet elements, ensuring alignment
        Janet *element_ptr = (Janet *)(data + i * sizeof(Janet));
        if ((uintptr_t)element_ptr % sizeof(Janet) == 0) {
            janet_elements[i] = *element_ptr;
        } else {
            janet_elements[i] = janet_wrap_nil(); // Use a default value if misaligned
        }
    }

    // Call the function-under-test
    JanetArray *result = janet_array_n(janet_elements, num_elements);

    // Clean up
    free(janet_elements);

    // Deinitialize the Janet runtime
    janet_deinit();

    // Optionally, handle the result if needed
    // For fuzzing purposes, we don't need to do anything with the result

    return 0;
}