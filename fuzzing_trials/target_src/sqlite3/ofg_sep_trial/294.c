#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_294(const uint8_t *data, size_t size) {
    void *ptr = NULL;
    sqlite3_uint64 newSize;

    // Ensure the size is at least 8 bytes to safely extract a sqlite3_uint64
    if (size < sizeof(sqlite3_uint64)) {
        return 0;
    }

    // Extract a sqlite3_uint64 from the input data
    newSize = *((sqlite3_uint64 *)data);

    // Allocate initial memory block
    ptr = sqlite3_malloc(64);  // Start with an arbitrary non-zero size
    if (ptr == NULL) {
        return 0;
    }

    // Call the function under test
    ptr = sqlite3_realloc64(ptr, newSize);

    // Free the allocated memory
    sqlite3_free(ptr);

    return 0;
}