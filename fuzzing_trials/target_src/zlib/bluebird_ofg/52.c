#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "inttypes.h" // Include for PRId64
#include "zlib.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters of adler32_combine
    uLong adler1 = 1; // Initial value for Adler-32 checksum
    uLong adler2 = 1; // Initial value for Adler-32 checksum
    int64_t len2 = 0; // Length of the second data block

    // Ensure the size is large enough to extract meaningful data
    if (size >= sizeof(uLong) * 2 + sizeof(int64_t)) {
        // Extract values from the input data
        adler1 = *(const uLong *)data;
        adler2 = *(const uLong *)(data + sizeof(uLong));
        len2 = *(const int64_t *)(data + sizeof(uLong) * 2);
    }

    // Call the function-under-test (using adler32_combine instead of adler32_combine64)
    uLong result = adler32_combine(adler1, adler2, len2);

    // Print the result for debugging purposes
    printf("adler32_combine result: %lu\n", result);

    return 0;
}