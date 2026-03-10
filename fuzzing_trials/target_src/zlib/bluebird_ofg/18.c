#include <stdint.h>
#include <stddef.h>
#include "sys/types.h" // Include this for off_t
#include "zlib.h"

// Function prototype for the function-under-test
uLong adler32_combine64(uLong adler1, uLong adler2, off_t len2);

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract three values
    if (size < sizeof(uLong) * 2 + sizeof(off_t)) {
        return 0;
    }

    // Extract uLong values from the input data
    uLong adler1 = *((const uLong *)data);
    uLong adler2 = *((const uLong *)(data + sizeof(uLong)));

    // Extract off_t value from the input data
    off_t len2 = *((const off_t *)(data + sizeof(uLong) * 2));

    // Call the function-under-test
    uLong result = adler32_combine64(adler1, adler2, len2);

    // Use the result in some way to prevent optimization out
    if (result == 0) {
        // Do something trivial
        return 0;
    }

    return 0;
}