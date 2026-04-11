#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
unsigned int hts_features();

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Call the function-under-test
    unsigned int features = hts_features();

    // Use the returned features value in some way to avoid compiler optimizations
    // that might remove the call to hts_features if the result is not used.
    // For example, print the features value (in a real fuzzing scenario, this
    // would not be necessary, but it's useful for debugging).
    (void)features; // Avoid unused variable warning

    return 0;
}