#include <stdint.h>
#include <zlib.h>

// Declare the crc32_combine_gen64 function if it's not declared in the included headers
uLong crc32_combine_gen64(int64_t offset);

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an int64_t value
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Extract an int64_t value from the input data
    int64_t offset = 0;
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
        offset = (offset << 8) | data[i];
    }

    // Call the function-under-test
    uLong result = crc32_combine_gen64(offset);

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    return 0;
}