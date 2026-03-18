#include <stdint.h>
#include <zlib.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Use the first few bytes of data to generate a uLong input for compressBound
    uLong input = 0;
    for (size_t i = 0; i < sizeof(uLong) && i < size; i++) {
        input = (input << 8) | data[i];
    }

    // Call the function-under-test
    uLong bound = compressBound(input);

    // Optionally, use the result in some way to prevent optimizations from removing the call
    (void)bound;

    return 0;
}