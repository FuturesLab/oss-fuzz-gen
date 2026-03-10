#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Call the function-under-test
    uLong flags = zlibCompileFlags();

    // Optionally use the input data in some way to make the fuzzing more effective
    // For example, if the function-under-test could take input, use it here
    // This is just a placeholder for demonstration purposes
    if (size > 0) {
        // Use the first byte of data in some way
        uint8_t first_byte = data[0];
        // Perform some operation with first_byte if applicable
    }

    // Use the result in some way, for example, print it for debugging purposes
    // (In actual fuzzing, you might not print to avoid slowing down the process)
    // printf("zlibCompileFlags: %lu\n", flags);

    return 0;
}