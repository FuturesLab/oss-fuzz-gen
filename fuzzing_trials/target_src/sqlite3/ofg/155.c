#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Ensure we have enough data for a sqlite3_int64
    if (size < sizeof(sqlite3_int64)) {
        return 0;
    }

    // Extract a sqlite3_int64 value from the input data
    sqlite3_int64 heap_limit = 0;
    for (size_t i = 0; i < sizeof(sqlite3_int64); i++) {
        heap_limit |= ((sqlite3_int64)data[i]) << (i * 8);
    }

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_hard_heap_limit64(heap_limit);

    // Use the result in some way to avoid compiler optimizations that might skip the call
    volatile sqlite3_int64 use_result = result;
    (void)use_result;

    return 0;
}