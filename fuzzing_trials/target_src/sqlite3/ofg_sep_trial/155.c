#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    sqlite3_int64 input_value;

    // Ensure that the input size is sufficient to form a sqlite3_int64 value
    if (size < sizeof(sqlite3_int64)) {
        return 0;
    }

    // Copy the first 8 bytes of data into input_value
    input_value = *((sqlite3_int64*)data);

    // Call the function-under-test
    sqlite3_int64 result = sqlite3_hard_heap_limit64(input_value);

    // Use the result in some way to avoid any compiler optimizations
    (void)result;

    return 0;
}