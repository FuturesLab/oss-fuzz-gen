#include <stdint.h>
#include <stddef.h>
#include <stdio.h>  // Include this for stderr

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        fprintf(stderr, "Failed to initialize magic\n");
        return 0; // If initialization fails, exit early
    }

    // Load a magic database to ensure the magic_set is properly initialized
    // You may specify a path to a magic database file if available
    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        return 0; // If loading fails, exit early
    }

    // Ensure the input data is not null and has a reasonable size
    if (size > 0 && data != NULL) {
        // Use the data provided by the fuzzer as input to the magic_buffer function
        const char *result = magic_buffer(magic, data, size);
        if (result != NULL) {
            // Print the result to ensure the function is being utilized
            // This can help in debugging and understanding what the function returns
            fprintf(stderr, "Magic result: %s\n", result);
        } else {
            // Print an error message if magic_buffer fails to process the input
            fprintf(stderr, "Magic buffer failed to process the input: %s\n", magic_error(magic));
        }
    } else {
        // Log a message if the input data is not suitable
        fprintf(stderr, "Invalid input data\n");
    }

    // Clean up
    magic_close(magic);

    return 0;
}