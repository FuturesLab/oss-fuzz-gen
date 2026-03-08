#include "stdint.h"
#include "stddef.h"
#include "stdio.h"

extern "C" {
    // Include the header file where magic_version is declared, if available.
    // If not, declare the function here for demonstration purposes.
    int magic_version();
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = magic_version();

    // Print the version for debugging purposes
    printf("Magic version: %d\n", version);

    return 0;
}