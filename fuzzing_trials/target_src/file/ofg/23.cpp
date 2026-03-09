#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <magic.h>
#include <iostream> // Include for logging purposes

extern "C" {
    // Include the necessary C headers and declare the function-under-test
    #include "magic.h"
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *magic;

    // Check if the input size is zero, if so, return early
    if (size == 0) {
        return 0;
    }

    // Initialize the magic_set structure
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // Return early if magic_open fails
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0; // Return early if magic_load fails
    }

    // Ensure the input data is not null and has a reasonable size
    if (data != NULL && size > 0) {
        // Call the function-under-test with the fuzzing input data
        const char *result = magic_buffer(magic, data, size);

        // Check the result to ensure it's not NULL and process it
        if (result != NULL) {
            // Log the result to ensure the function is being exercised
            std::cout << "Result: " << result << std::endl;
        }
    }

    // Clean up
    magic_close(magic);

    return 0;
}