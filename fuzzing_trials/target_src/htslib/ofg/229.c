#include <stdint.h>
#include <stddef.h>

// Function-under-test
double bam_auxB2f(const uint8_t *data, uint32_t size);

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid passing a NULL pointer
    if (size == 0) return 0;

    // Call the function-under-test with the provided data and size
    double result = bam_auxB2f(data, (uint32_t)size);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile double use_result = result;
    (void)use_result;

    return 0;
}