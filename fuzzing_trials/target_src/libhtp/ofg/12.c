#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Function-under-test declaration
char * htp_get_version();

// Fuzzing harness
int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Call the function-under-test
    char *version = htp_get_version();

    // Print the version string to verify the function call
    if (version != NULL) {
        printf("HTP Version: %s\n", version);
    }

    return 0;
}