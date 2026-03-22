#include <stddef.h>
#include <stdint.h>

// Function-under-test declaration
unsigned int dwarf_basic_crc32(const unsigned char *buf, unsigned long len, unsigned int crc);

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the function parameters
    if (size < 1) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    const unsigned char *buf = data;  // Use the input data as the buffer
    unsigned long len = size;         // Use the size of the data as the length
    unsigned int crc = 0;             // Initialize CRC with a non-zero value

    // Call the function-under-test
    unsigned int result = dwarf_basic_crc32(buf, len, crc);

    // Use the result to prevent any compiler optimizations that might skip the call
    (void)result;

    return 0;
}