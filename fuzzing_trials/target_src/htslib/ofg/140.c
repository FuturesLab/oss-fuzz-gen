#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Function declaration
const char *hts_version();

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = hts_version();

    // Print the version to ensure the function is called
    printf("HTS Version: %s\n", version);

    return 0;
}