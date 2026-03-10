#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure size is at least the size of an off_t
    if (size < sizeof(off_t)) {
        return 0;
    }

    // Extract an off_t value from the input data
    off_t offset = 0;
    for (size_t i = 0; i < sizeof(off_t); ++i) {
        offset = (offset << 8) | data[i];
    }

    // Call the function-under-test
    uLong result = crc32_combine_gen(offset);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result == 0) {
        return 0;
    }

    return 0;
}