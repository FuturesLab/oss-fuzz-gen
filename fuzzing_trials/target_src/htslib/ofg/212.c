#include <stdint.h>
#include <stdio.h>

// Assuming the function hts_features is defined in an external library
extern unsigned int hts_features();

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Call the function-under-test
    unsigned int features = hts_features();

    // Print the result for debugging purposes
    printf("hts_features returned: %u\n", features);

    return 0;
}