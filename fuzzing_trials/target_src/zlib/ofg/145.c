#include <stdint.h>
#include <stddef.h>
#include <zlib.h> // Ensure this header is available for crc32_combine_op

// Remove the 'extern "C"' linkage specification for C code
int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Declare and initialize the three uLong parameters for the function
    uLong crc1 = 0;
    uLong crc2 = 0;
    uLong len2 = 0;

    // Ensure size is sufficient to extract three uLong values
    if (size >= 3 * sizeof(uLong)) {
        // Extract uLong values from the input data
        crc1 = *((uLong *)(data));
        crc2 = *((uLong *)(data + sizeof(uLong)));
        len2 = *((uLong *)(data + 2 * sizeof(uLong)));
    }

    // Call the function-under-test
    uLong result = crc32_combine_op(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations
    volatile uLong use_result = result;
    (void)use_result;

    return 0;
}