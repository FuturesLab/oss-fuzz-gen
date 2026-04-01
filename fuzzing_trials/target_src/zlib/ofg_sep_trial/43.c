#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of uLong
    if (size < sizeof(uLong)) {
        return 0;
    }

    // Interpret the first bytes of data as a uLong
    uLong input = 0;
    for (size_t i = 0; i < sizeof(uLong); ++i) {
        input |= ((uLong)data[i]) << (i * 8);
    }

    // Call the function-under-test
    uLong result = compressBound(input);

    // Use the result in some way to prevent compiler optimizations
    if (result == 0) {
        return 1;
    }

    return 0;
}