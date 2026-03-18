#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    sqlite3_int64 limit = 0;

    // Ensure that the size is at least the size of sqlite3_int64
    if (size >= sizeof(sqlite3_int64)) {
        // Copy data into limit, ensuring that it is properly aligned
        limit = *((sqlite3_int64*)data);
    }

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_hard_heap_limit64(limit);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}