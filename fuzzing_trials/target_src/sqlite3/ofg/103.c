#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Declare and initialize the parameter for sqlite3_soft_heap_limit64
    sqlite3_int64 heap_limit = 0;

    // Ensure that the size of the input data is sufficient to extract a sqlite3_int64 value
    if (size >= sizeof(sqlite3_int64)) {
        // Copy bytes from data to heap_limit to form a valid sqlite3_int64 value
        heap_limit = *(const sqlite3_int64 *)data;
    }

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_soft_heap_limit64(heap_limit);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}