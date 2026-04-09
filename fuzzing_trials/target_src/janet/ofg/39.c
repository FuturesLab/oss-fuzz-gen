#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

extern void *janet_scalloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two size_t values
    if (size < sizeof(size_t) * 2) {
        return 0;
    }

    // Extract two size_t values from the input data
    size_t num = *((const size_t *)data);
    size_t elem_size = *((const size_t *)(data + sizeof(size_t)));

    // Avoid trivial cases by ensuring num and elem_size are non-zero
    if (num == 0) {
        num = 1;
    }
    if (elem_size == 0) {
        elem_size = 1;
    }

    // Avoid potential overflow in size calculation
    if (num > SIZE_MAX / elem_size) {
        return 0;
    }

    // Call the function-under-test
    void *result = janet_scalloc(num, elem_size);

    // If allocation succeeded, perform further operations to test memory
    if (result != NULL) {
        // Fill the allocated memory with a pattern
        memset(result, 0xAA, num * elem_size);

        // Optionally, perform some reads to simulate usage
        for (size_t i = 0; i < num * elem_size; i++) {
            volatile uint8_t temp = ((uint8_t *)result)[i];
            (void)temp; // Use temp to avoid compiler optimizations
        }

        // Free the allocated memory
        free(result);
    }

    return 0;
}