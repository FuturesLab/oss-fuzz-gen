#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>  // For the definition of off_t

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract three values
    if (size < sizeof(uLong) * 2 + sizeof(off_t)) {
        return 0;
    }

    // Extract uLong values from the data
    uLong crc1 = *(const uLong *)(data);
    uLong crc2 = *(const uLong *)(data + sizeof(uLong));

    // Extract off_t value from the data
    off_t len2 = *(const off_t *)(data + sizeof(uLong) * 2);

    // Call the function-under-test
    uLong result = crc32_combine(crc1, crc2, len2);

    // Use the result to avoid compiler optimizations removing the function call
    volatile uLong prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}