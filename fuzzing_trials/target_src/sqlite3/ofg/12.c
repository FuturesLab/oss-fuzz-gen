#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Call the function-under-test
    sqlite3_int64 memory_used = sqlite3_memory_used();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (memory_used > 0) {
        // Do something trivial with the result
        volatile sqlite3_int64 dummy = memory_used;
        (void)dummy; // Suppress unused variable warning
    }

    return 0;
}