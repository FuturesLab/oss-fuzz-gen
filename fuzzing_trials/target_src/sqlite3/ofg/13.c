#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Call the function-under-test
    sqlite3_int64 memoryUsed = sqlite3_memory_used();

    // Use the result in some way to avoid compiler optimizations
    if (memoryUsed > 0) {
        // Do something trivial with the result
        volatile sqlite3_int64 dummy = memoryUsed;
        (void)dummy; // Suppress unused variable warning
    }

    return 0;
}