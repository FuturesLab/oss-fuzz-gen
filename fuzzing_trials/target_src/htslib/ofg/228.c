#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
double bam_auxB2f(const uint8_t *data, uint32_t size);

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    // Ensure size is within the range of uint32_t
    if (size == 0 || size > UINT32_MAX) {
        return 0;
    }

    // Call the function-under-test with the provided data and size
    double result = bam_auxB2f(data, (uint32_t)size);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}