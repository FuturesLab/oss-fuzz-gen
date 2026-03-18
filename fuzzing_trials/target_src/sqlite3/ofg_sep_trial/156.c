#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Declare and initialize the variable to be used as input
    sqlite3_int64 limit = 0;

    // Ensure the size is sufficient to read a sqlite3_int64 value
    if (size >= sizeof(sqlite3_int64)) {
        // Copy the first sizeof(sqlite3_int64) bytes from data into limit
        limit = *(const sqlite3_int64 *)data;
    }

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_hard_heap_limit64(limit);

    // Use the result in some way to prevent any compiler optimizations
    // that might remove the function call
    volatile sqlite3_int64 use_result = result;
    (void)use_result;

    return 0;
}