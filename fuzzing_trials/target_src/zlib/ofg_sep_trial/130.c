#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Call the function-under-test
    uLong flags = zlibCompileFlags();

    // Use the input data in some way to ensure it is not null
    // Here, we simply check if the size is greater than zero and use the first byte
    if (size > 0) {
        // Use the first byte of data to do something, e.g., print or check
        uint8_t first_byte = data[0];
        // For demonstration, we just use the first_byte in some way
        (void)first_byte; // To avoid unused variable warning
    }

    // Use the flags in some way to ensure the call is not optimized away
    (void)flags; // To avoid unused variable warning

    return 0;
}