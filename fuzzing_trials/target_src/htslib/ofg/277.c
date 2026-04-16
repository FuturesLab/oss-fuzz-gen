#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Function signature
int hts_resize_array_(size_t, size_t, size_t, void *, void **, int, const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_277(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract meaningful values
    if (size < sizeof(size_t) * 3 + sizeof(int) + 1) {
        return 0;
    }

    // Extract size_t values from the input data
    size_t size1 = *((size_t *)data);
    size_t size2 = *((size_t *)(data + sizeof(size_t)));
    size_t size3 = *((size_t *)(data + 2 * sizeof(size_t)));

    // Extract an integer value from the input data
    int int_val = *((int *)(data + 3 * sizeof(size_t)));

    // Extract a string from the input data
    const char *string_val = (const char *)(data + 3 * sizeof(size_t) + sizeof(int));

    // Ensure size1, size2, and size3 do not cause overflow in multiplication
    if (size1 > 0 && size2 > 0 && size3 > 0 && size1 <= SIZE_MAX / size2 && size1 * size2 <= SIZE_MAX / size3) {
        // Allocate memory for the array
        void *array = malloc(size1 * size2 * size3);
        if (array == NULL) {
            return 0;  // Exit if memory allocation fails
        }

        // Initialize a pointer to the array
        void *array_ptr = array;

        // Call the function-under-test
        hts_resize_array_(size1, size2, size3, array, &array_ptr, int_val, string_val);

        // Free allocated memory
        free(array);
    }

    return 0;
}