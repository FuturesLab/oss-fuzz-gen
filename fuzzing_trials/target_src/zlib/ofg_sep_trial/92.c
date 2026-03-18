#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <sys/types.h> // Include this for off64_t
#include <inttypes.h>  // Include this for PRId64

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract three values
    if (size < sizeof(uLong) * 2 + sizeof(int64_t)) {
        return 0;
    }

    // Initialize the parameters for crc32_combine64
    uLong crc1 = *(const uLong *)(data);
    uLong crc2 = *(const uLong *)(data + sizeof(uLong));
    int64_t len2 = *(const int64_t *)(data + sizeof(uLong) * 2);

    // Call the function-under-test
    uLong result = crc32_combine(crc1, crc2, (z_off_t)len2);

    // Use the result to prevent the compiler from optimizing the call away
    (void)result;

    return 0;
}