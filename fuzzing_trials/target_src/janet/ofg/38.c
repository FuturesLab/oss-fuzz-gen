#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Function-under-test declaration
void *janet_scalloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two size_t values
    if (size < 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract two size_t values from the input data
    size_t num = *((size_t *)data);
    size_t elem_size = *((size_t *)(data + sizeof(size_t)));

    // Limit the size of num and elem_size to avoid excessive memory allocation
    // Ensure num and elem_size are at least 1 to avoid trivial allocations
    num = (num % (SIZE_MAX / 2)) + 1;
    elem_size = (elem_size % (SIZE_MAX / 2)) + 1;

    // Call the function-under-test
    void *result = janet_scalloc(num, elem_size);

    // Check if the allocation was successful
    if (result != NULL) {
        // Write some data to the allocated memory to simulate usage
        memset(result, 0xAA, num * elem_size);

        // Introduce a deliberate out-of-bounds write to test for memory corruption detection
        // Adjusted to ensure the out-of-bounds write happens within bounds
        if (num * elem_size > 0) {
            // Perform a deliberate out-of-bounds write just beyond the allocated memory
            if (num * elem_size < SIZE_MAX) {
                ((uint8_t *)result)[num * elem_size] = 0xBB; // Out-of-bounds write
            }
        }

        // Free the allocated memory
        free(result);
    }

    return 0;
}