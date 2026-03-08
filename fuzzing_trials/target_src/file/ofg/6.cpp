#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" {
    // Include the function-under-test
    int magic_check(struct magic_set *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize the magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // If initialization fails, return immediately
    }

    // Ensure the input data is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        magic_close(magic);
        return 0; // If memory allocation fails, return immediately
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    magic_check(magic, input);

    // Clean up
    free(input);
    magic_close(magic);

    return 0;
}