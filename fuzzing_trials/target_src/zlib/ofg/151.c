#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>  // Include for int64_t
#include <zlib.h>      // Ensure to include the zlib header for the function signature

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    uLong adler1 = 1;  // Initial adler32 checksum value
    uLong adler2 = 1;  // Another adler32 checksum value
    int64_t len2 = 0;  // Length of the second part

    // Ensure size is large enough to extract meaningful values
    if (size >= sizeof(uLong) * 2 + sizeof(int64_t)) {
        // Extract adler1, adler2, and len2 from the input data
        adler1 = *(const uLong *)(data);
        adler2 = *(const uLong *)(data + sizeof(uLong));
        len2 = *(const int64_t *)(data + sizeof(uLong) * 2);
    }

    // Call the function-under-test
    uLong result = adler32_combine(adler1, adler2, len2);

    // Use the result to prevent any compiler optimizations
    (void)result;

    return 0;
}

#ifdef __cplusplus
}
#endif