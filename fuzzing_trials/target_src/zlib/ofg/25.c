#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = zlibVersion();

    // Print the version to ensure the function is called
    printf("Zlib version: %s\n", version);

    return 0;
}