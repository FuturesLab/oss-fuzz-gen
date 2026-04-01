#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    sqlite3_int64 limit;
    
    // Ensure that there is enough data to read a sqlite3_int64 value
    if (size < sizeof(sqlite3_int64)) {
        return 0;
    }

    // Copy the data into a sqlite3_int64 variable
    limit = *((sqlite3_int64*)data);

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_soft_heap_limit64(limit);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}