#include <stdint.h>
#include <stddef.h>
#include <zlib.h> // Ensure zlib is installed and linked during compilation
#include <inttypes.h> // Include for fixed width integer types

// Remove extern "C" as it is not valid in C code
int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Ensure size is large enough to extract three values
    if (size < sizeof(uLong) * 2 + sizeof(int64_t)) {
        return 0;
    }

    // Extract uLong values from the input data
    uLong crc1 = *(const uLong *)(data);
    uLong crc2 = *(const uLong *)(data + sizeof(uLong));

    // Extract int64_t value from the input data
    int64_t len2 = *(const int64_t *)(data + sizeof(uLong) * 2);

    // Call the function-under-test
    uLong result = crc32_combine64(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}