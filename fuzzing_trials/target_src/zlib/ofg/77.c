#include <stdint.h>
#include <zlib.h>
#include <stddef.h> // Include this header for size_t
#include <inttypes.h> // Include this header for int64_t

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of int64_t
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Extract an int64_t value from the input data
    int64_t offset = 0;
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
        offset |= ((int64_t)data[i]) << (i * 8);
    }

    // Call the function-under-test
    uLong result = crc32_combine_gen64(offset);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile uLong use_result = result;
    (void)use_result;

    return 0;
}