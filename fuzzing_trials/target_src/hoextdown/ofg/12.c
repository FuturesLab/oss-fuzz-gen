#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

// Function-under-test
void * hoedown_calloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two size_t values
    if (size < 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract two size_t values from the data
    size_t num = *((size_t *)data);
    size_t elem_size = *((size_t *)(data + sizeof(size_t)));

    // Add checks to ensure the parameters are within a reasonable range
    // to prevent excessive memory allocation or integer overflow.
    if (num > SIZE_MAX / elem_size || elem_size > SIZE_MAX / num) {
        return 0;
    }

    // Call the function-under-test
    void *result = hoedown_calloc(num, elem_size);

    // Free the allocated memory if not NULL
    if (result != NULL) {
        free(result);
    }

    return 0;
}