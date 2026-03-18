#include <stdint.h>
#include <stddef.h>
#include <sys/types.h> // Include this for off_t
#include <zlib.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    uLong adler1 = 1; // Initialize with a non-zero value
    uLong adler2 = 1; // Initialize with a non-zero value
    off_t len2 = 0; // Initialize with zero

    if (size >= sizeof(uLong) * 2 + sizeof(off_t)) {
        // Extract values from the data if size is sufficient
        adler1 = *(const uLong *)data;
        adler2 = *(const uLong *)(data + sizeof(uLong));
        len2 = *(const off_t *)(data + 2 * sizeof(uLong));
    }

    // Use adler32_combine instead of the non-existent adler32_combine_
    uLong result = adler32_combine(adler1, adler2, len2);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}