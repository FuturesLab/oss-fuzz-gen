#include <stddef.h>  // Include for size_t
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    int flag = 0;

    if (size > 0) {
        // Use the first byte of data to determine the flag value
        flag = (int)data[0];
    }

    // Call the function-under-test
    sqlite3_int64 highwater = sqlite3_memory_highwater(flag);

    // Use the result in some way to prevent the compiler from optimizing it away
    if (highwater != 0) {
        // Do nothing, just a placeholder to use the variable
    }

    return 0;
}