#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = zlibVersion();

    // Use the version string in some way to ensure it is accessed
    if (version != NULL && size > 0) {
        // Do something trivial with the version string and input data
        // to prevent compiler optimizations from removing the call
        if (data[0] == version[0]) {
            // This is just a dummy check to use the variables
        }
    }

    return 0;
}