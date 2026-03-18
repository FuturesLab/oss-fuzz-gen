#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Declare and initialize the uLong variables
    uLong crc1 = 0;
    uLong crc2 = 0;
    uLong len2 = 0;

    // Ensure that the input size is sufficient to extract three uLong values
    if (size < sizeof(uLong) * 3) {
        return 0;
    }

    // Extract the uLong values from the input data
    crc1 = *(const uLong *)(data);
    crc2 = *(const uLong *)(data + sizeof(uLong));
    len2 = *(const uLong *)(data + 2 * sizeof(uLong));

    // Call the function-under-test
    uLong result = crc32_combine_op(crc1, crc2, len2);

    // Use the result in some way to prevent any compiler optimizations from removing the call
    (void)result;

    return 0;
}