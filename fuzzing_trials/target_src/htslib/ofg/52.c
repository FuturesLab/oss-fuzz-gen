#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
double bam_aux2f(const uint8_t *data);

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has at least one byte
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    double result = bam_aux2f(data);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}