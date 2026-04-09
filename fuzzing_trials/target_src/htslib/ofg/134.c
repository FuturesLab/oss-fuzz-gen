#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Function-under-test
const char * hts_feature_string();

// Fuzzing harness
int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *features = hts_feature_string();

    // Use the result to prevent compiler warnings about unused variables
    if (features != NULL) {
        // Print the result to ensure the function is being exercised
        // This helps in verifying that different outputs are being generated
        printf("Features: %s\n", features);
    }

    return 0;
}