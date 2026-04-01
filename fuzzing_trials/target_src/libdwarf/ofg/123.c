#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
unsigned int dwarf_basic_crc32(const unsigned char *buf, unsigned long len, unsigned int crc);

// Fuzzing harness
int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid passing NULL pointers
    if (size == 0) {
        return 0;
    }

    // Use the first 4 bytes of data as the initial CRC value if available
    unsigned int initial_crc = 0;
    if (size >= 4) {
        initial_crc = *(unsigned int *)data;
    }

    // Call the function-under-test
    unsigned int result = dwarf_basic_crc32(data, (unsigned long)size, initial_crc);

    // Use the result in some way to avoid optimizing out the call
    if (result == 0) {
        // Do nothing, just a placeholder to use the result
    }

    return 0;
}