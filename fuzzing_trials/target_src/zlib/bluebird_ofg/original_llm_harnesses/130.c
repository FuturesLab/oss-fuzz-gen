#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Call the function-under-test
    uLong flags = zlibCompileFlags();

    // Use the result in some way to avoid compiler optimizations removing the call
    // Here, we simply print the flags value, but in a real fuzzing scenario, you might
    // want to perform further operations based on the flags value.
    (void)flags; // Suppress unused variable warning

    // Simulate using the input data to maximize fuzzing result
    if (size > 0) {
        // Example operation: feed the data to a zlib function
        uLong crc = crc32(0L, Z_NULL, 0);
        crc = crc32(crc, data, size);
        (void)crc; // Suppress unused variable warning
    }

    return 0;
}