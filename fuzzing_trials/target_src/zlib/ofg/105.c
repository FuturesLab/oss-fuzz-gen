#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Initialize the parameters for crc32_combine
    uLong crc1 = 0;  // Initial CRC value for the first part
    uLong crc2 = 0;  // Initial CRC value for the second part
    off_t len2 = 0;  // Length of the second part

    // Ensure the data is large enough to extract meaningful values
    if (size >= sizeof(uLong) * 2 + sizeof(off_t)) {
        // Extract values from the input data
        crc1 = *(const uLong *)data;
        crc2 = *(const uLong *)(data + sizeof(uLong));
        len2 = *(const off_t *)(data + sizeof(uLong) * 2);
    }

    // Call the function-under-test
    uLong combined_crc = crc32_combine(crc1, crc2, len2);

    // Use the combined_crc in some way to avoid compiler optimizations
    (void)combined_crc;

    return 0;
}