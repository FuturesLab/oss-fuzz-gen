#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Declare and initialize the input parameter for the function-under-test
    sqlite3_int64 heap_limit = 0;

    // Ensure the size is sufficient to extract a sqlite3_int64 value
    if (size >= sizeof(sqlite3_int64)) {
        // Copy the data into the heap_limit variable
        heap_limit = *(const sqlite3_int64 *)data;
    }

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_soft_heap_limit64(heap_limit);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}