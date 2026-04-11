#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
int bam_str2flag(const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely pass as a string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    int result = bam_str2flag(input);

    // Clean up
    free(input);

    return 0;
}