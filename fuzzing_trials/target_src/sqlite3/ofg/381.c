#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>  // Include the SQLite3 header for sqlite3_malloc

int LLVMFuzzerTestOneInput_381(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the size for sqlite3_malloc
    int malloc_size = (int)data[0];

    // Call the function-under-test
    void *allocated_memory = sqlite3_malloc(malloc_size);

    // Free the allocated memory if it is not NULL
    if (allocated_memory != NULL) {
        sqlite3_free(allocated_memory);
    }

    return 0;
}