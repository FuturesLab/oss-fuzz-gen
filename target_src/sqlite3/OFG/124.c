#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Ensure that size is greater than 0 to avoid passing NULL to sqlite3_free
    if (size == 0) {
        return 0;
    }

    // Allocate memory to hold the input data
    void *ptr = sqlite3_malloc(size);
    if (ptr == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Copy the input data into the allocated memory
    memcpy(ptr, data, size);

    // Call the function under test
    sqlite3_free(ptr);

    return 0;
}