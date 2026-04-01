#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    sqlite3_int64 limit = 0;

    // Ensure the input size is sufficient to extract a sqlite3_int64 value
    if (size >= sizeof(sqlite3_int64)) {
        // Copy the first sizeof(sqlite3_int64) bytes from data to limit
        limit = *(const sqlite3_int64 *)data;
    }

    // Call the function-under-test with the extracted limit value
    sqlite3_int64 result = sqlite3_soft_heap_limit64(limit);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}