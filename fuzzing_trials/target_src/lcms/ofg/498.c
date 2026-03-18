#include <stdint.h>
#include <stddef.h>  // Include this header to define 'size_t'

// Function-under-test declaration
int cmsGetEncodedCMMversion();

// Fuzzing harness
int LLVMFuzzerTestOneInput_498(const uint8_t *data, size_t size) {
    // Directly call the function-under-test
    int version = cmsGetEncodedCMMversion();

    // Use the returned version for some basic operation to avoid compiler optimizations
    if (version == 0) {
        return 0;
    }

    // Additional logic to use the input data
    if (size > 0) {
        // Use the first byte of data for some operation
        uint8_t first_byte = data[0];
        // Perform some operation with first_byte and version
        if (first_byte == (uint8_t)version) {
            return 1;
        }
    }

    return 0;
}