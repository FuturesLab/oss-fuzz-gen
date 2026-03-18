#include <cstddef>  // For size_t
#include <cstdint>  // For uint8_t
#include <cstdlib>  // For NULL
#include <cstdio>   // For printf

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // If the input size is zero, return immediately as there's nothing to process
    if (size == 0) {
        return 0;
    }

    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    
    // Check if magic_open was successful
    if (magic == NULL) {
        return 0; // Exit if magic_open failed
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0; // Exit if magic_load failed
    }

    // Use magic_buffer to analyze the input data
    const char *result = magic_buffer(magic, data, size);
    if (result != NULL) {
        // Print the result for debugging purposes
        printf("Magic result: %s\n", result);
    } else {
        // Print an error message if magic_buffer returns NULL
        printf("Magic buffer returned NULL: %s\n", magic_error(magic));
    }

    // Clean up
    magic_close(magic);

    return 0;
}