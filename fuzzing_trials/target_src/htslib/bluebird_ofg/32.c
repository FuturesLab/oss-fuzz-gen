#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
const char * hts_test_feature(unsigned int feature);

// Fuzzing harness
int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int feature = *((unsigned int *)data);

    // Call the function-under-test
    const char *result = hts_test_feature(feature);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        // For example, we can check the first character
        volatile char first_char = result[0];
    }

    return 0;
}