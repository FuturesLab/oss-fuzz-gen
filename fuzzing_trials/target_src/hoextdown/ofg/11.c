#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

// Function-under-test
void *hoedown_calloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract two size_t values
    if (size < 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract two size_t values from the input data
    size_t num = *(const size_t *)data;
    size_t elem_size = *(const size_t *)(data + sizeof(size_t));

    // Check for overflow condition
    if (num != 0 && elem_size > SIZE_MAX / num) {
        return 0;
    }

    // Call the function-under-test
    void *result = hoedown_calloc(num, elem_size);

    // Free the allocated memory if the call was successful
    if (result != NULL) {
        free(result);
    }

    return 0;
}