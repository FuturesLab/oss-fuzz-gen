#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
int64_t bam_auxB2i(const uint8_t *data, uint32_t size);

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure that the size fits within the range of a uint32_t
    if (size > UINT32_MAX) {
        return 0;
    }

    // Call the function-under-test with the given data and size
    int64_t result = bam_auxB2i(data, (uint32_t)size);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}