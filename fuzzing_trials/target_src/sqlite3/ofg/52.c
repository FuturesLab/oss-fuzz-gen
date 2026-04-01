#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to interpret as an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first few bytes of data as an integer
    int flag = *(int*)data;

    // Call the function-under-test
    sqlite3_int64 highwater = sqlite3_memory_highwater(flag);

    // Use highwater in some way to prevent compiler optimizations from removing the call
    volatile sqlite3_int64 use_result = highwater;
    (void)use_result; // Prevent unused variable warning

    return 0;
}