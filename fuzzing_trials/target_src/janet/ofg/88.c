#include <stddef.h>
#include <stdint.h>

// Assume the function is defined elsewhere
void *janet_calloc(size_t num, size_t size);

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Ensure there's enough data to read two size_t values
    if (size < 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract two size_t values from the input data
    size_t num = ((size_t *)data)[0];
    size_t elem_size = ((size_t *)data)[1];

    // Call the function-under-test
    void *result = janet_calloc(num, elem_size);

    // Free the allocated memory if not NULL
    if (result != NULL) {
        free(result);
    }

    return 0;
}