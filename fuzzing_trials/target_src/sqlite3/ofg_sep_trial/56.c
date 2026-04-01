#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int param = *(int *)data;

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_memory_highwater(param);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != 0) {
        // Do something trivial with the result
        volatile sqlite3_int64 temp = result;
        (void)temp;
    }

    return 0;
}