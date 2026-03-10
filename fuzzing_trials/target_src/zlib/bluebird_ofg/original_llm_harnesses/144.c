#include <stdint.h>
#include <stddef.h>
#include <zlib.h> // Assuming crc32_combine_op is part of zlib

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    uLong crc1 = 0;
    uLong crc2 = 0;
    uLong len2 = 0;

    // Ensure the size is sufficient to extract three uLong values
    if (size >= sizeof(uLong) * 3) {
        // Extract values from the input data
        crc1 = *((const uLong *)data);
        crc2 = *((const uLong *)(data + sizeof(uLong)));
        len2 = *((const uLong *)(data + 2 * sizeof(uLong)));
    }

    // Call the function-under-test
    uLong combined_crc = crc32_combine_op(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations
    volatile uLong result = combined_crc;
    (void)result;

    return 0;
}