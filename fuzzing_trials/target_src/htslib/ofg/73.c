#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
int64_t bam_aux2i(const uint8_t *data);

// Fuzzing harness
int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure the input data is not NULL and has at least one byte
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test with the provided data
    int64_t result = bam_aux2i(data);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}