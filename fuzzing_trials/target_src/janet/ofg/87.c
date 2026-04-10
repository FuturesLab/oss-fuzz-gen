#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Function-under-test
void *janet_calloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two size_t values
    if (size < sizeof(size_t) * 2) {
        return 0;
    }

    // Extract two size_t values from the input data
    size_t num = *((const size_t *)data);
    size_t elem_size = *((const size_t *)(data + sizeof(size_t)));

    // Call the function-under-test
    void *result = janet_calloc(num, elem_size);

    // If the result is not NULL, free the allocated memory
    if (result != NULL) {
        free(result);
    }

    return 0;
}