#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

// Remove the 'extern "C"' as it is not needed in a C file
int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = zlibVersion();

    // Print the version to verify the function call
    printf("Zlib version: %s\n", version);

    // Utilize the input data to maximize fuzzing result
    if (size > 0) {
        // Example usage of data: calculate CRC32 checksum
        uLong crc = crc32(0L, Z_NULL, 0);
        crc = crc32(crc, data, size);
        printf("CRC32: %lu\n", crc);
    }

    return 0;
}