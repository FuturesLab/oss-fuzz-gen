#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <inttypes.h>  // Include for int64_t

// Define the fuzzing function for C
int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure that the input size is large enough to extract the necessary parameters.
    if (size < sizeof(uLong) * 2 + sizeof(int64_t)) {
        return 0;
    }

    // Extract uLong values from the input data.
    uLong crc1 = *(const uLong *)(data);
    uLong crc2 = *(const uLong *)(data + sizeof(uLong));

    // Extract int64_t value from the input data.
    int64_t len2 = *(const int64_t *)(data + sizeof(uLong) * 2);

    // Call the function-under-test with the extracted parameters.
    uLong result = crc32_combine64(crc1, crc2, len2);

    // Use the result in some way to avoid compiler optimizations removing the call.
    (void)result;

    return 0;
}