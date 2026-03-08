#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"
#include <cstdio>  // Include this for printf, fprintf, and stderr
#include "magic.h"

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "magic.h"
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    struct magic_set *magic = NULL;

    // Initialize the magic_set structure
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        fprintf(stderr, "Failed to initialize magic library\n");
        return 0;
    }

    // Load a magic database, using a specified path if needed
    // Replace "path/to/magic.mgc" with the actual path to the magic database if required
    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        return 0;
    }

    // Ensure the data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Call the function-under-test with the provided data
        const char *result = magic_buffer(magic, data, size);
        if (result != NULL) {
            // Log the result to verify the function is being exercised
            printf("Magic result: %s\n", result);
        } else {
            // Handle the case where magic_buffer returns NULL
            const char *error = magic_error(magic);
            if (error != NULL) {
                // Log the error
                fprintf(stderr, "Magic error: %s\n", error);
            }
        }
    }

    // Clean up
    magic_close(magic);

    return 0;
}