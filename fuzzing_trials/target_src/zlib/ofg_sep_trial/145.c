#include <stdint.h>
#include <stddef.h>
#include <zlib.h>  // Ensure zlib is installed and linked during compilation

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the crc32_combine function
    uLong crc1 = 0;
    uLong crc2 = 0;
    uLong len2 = 0;

    // Ensure size is large enough to extract three uLong values
    if (size >= 3 * sizeof(uLong)) {
        // Extract the first uLong value from data
        crc1 = *(const uLong *)(data);
        // Extract the second uLong value from data
        crc2 = *(const uLong *)(data + sizeof(uLong));
        // Extract the third uLong value from data
        len2 = *(const uLong *)(data + 2 * sizeof(uLong));
    }

    // Call the function-under-test
    uLong result = crc32_combine(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}