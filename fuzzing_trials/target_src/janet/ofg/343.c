#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

extern Janet janet_dyn(const char *);

int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    Janet result = janet_dyn(input);

    // Clean up
    free(input);

    return 0;
}