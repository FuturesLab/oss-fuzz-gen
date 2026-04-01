#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <magic.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Declare and initialize variables
    struct magic_set *magic = magic_open(MAGIC_NONE);
    const char *result = NULL;
    
    // Ensure magic is not NULL
    if (magic == NULL) {
        fprintf(stderr, "Failed to initialize magic library\n");
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test directly with the fuzzing input
    result = magic_buffer(magic, data, size);

    // Do something with the result if needed
    if (result != NULL) {
        // For example, print the result (not necessary for fuzzing)
        // printf("Magic Buffer: %s\n", result);
    } else {
        fprintf(stderr, "magic_buffer failed: %s\n", magic_error(magic));
    }

    // Clean up
    magic_close(magic);

    return 0;
}