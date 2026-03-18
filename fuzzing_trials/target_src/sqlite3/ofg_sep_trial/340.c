#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_340(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of sqlite3_uint64
    if (size < sizeof(sqlite3_uint64)) {
        return 0;
    }

    // Extract a sqlite3_uint64 value from the input data
    sqlite3_uint64 alloc_size = 0;
    for (size_t i = 0; i < sizeof(sqlite3_uint64); ++i) {
        alloc_size = (alloc_size << 8) | data[i];
    }

    // Call the function-under-test
    void *allocated_memory = sqlite3_malloc64(alloc_size);

    // Free the allocated memory if not NULL
    if (allocated_memory != NULL) {
        sqlite3_free(allocated_memory);
    }

    return 0;
}