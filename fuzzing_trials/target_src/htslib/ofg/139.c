#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Function prototype for the function-under-test
const char * hts_version();

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = hts_version();

    // Print the version for debugging purposes
    // (In a real fuzzing scenario, you might not print this, but it's useful for demonstration)
    printf("HTS Version: %s\n", version);

    return 0;
}