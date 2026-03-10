#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure that the input size is at least the size of uLong
    if (size < sizeof(uLong)) {
        return 0;
    }

    // Extract a uLong value from the input data
    uLong input_value = 0;
    for (size_t i = 0; i < sizeof(uLong); i++) {
        input_value |= ((uLong)data[i]) << (i * 8);
    }

    // Call the function-under-test
    uLong result = compressBound(input_value);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}