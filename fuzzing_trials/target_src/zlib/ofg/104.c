#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Initialize the parameters for crc32_combine
    uLong crc1 = 0xFFFFFFFF; // Example initial CRC value
    uLong crc2 = 0xFFFFFFFF; // Example initial CRC value
    off_t len2 = 1024; // Example length

    // Ensure the input size is large enough to extract values
    if (size >= sizeof(uLong) * 2 + sizeof(off_t)) {
        // Extract values from the input data
        crc1 = *(const uLong *)data;
        crc2 = *(const uLong *)(data + sizeof(uLong));
        len2 = *(const off_t *)(data + sizeof(uLong) * 2);
    }

    // Call the function-under-test
    uLong result = crc32_combine(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations
    volatile uLong use_result = result;
    (void)use_result;

    return 0;
}