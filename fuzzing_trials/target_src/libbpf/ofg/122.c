#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Function-under-test declaration
const char *libbpf_version_string();

// Fuzzing harness
int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = libbpf_version_string();
    
    // Print the version string to ensure the function is called
    if (version != NULL) {
        printf("libbpf version: %s\n", version);
    }

    return 0;
}