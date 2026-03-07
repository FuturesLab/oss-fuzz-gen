#include <cstdint>
#include <cstdlib>
#include <magic.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Check if the input size is valid
    if (size < 1) {
        return 0; // Return early if there's no data to process
    }

    // Initialize a magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // If magic_open fails, return early
    }

    // Load the magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0; // If magic_load fails, return early
    }

    // Use the magic_buffer function to analyze the input data
    const char *result = magic_buffer(ms, data, size);
    if (result != NULL) {
        // Example operation: print the result
        // Note: In a real fuzzing environment, printing is not recommended
        // std::cout << "Magic result: " << result << std::endl;
    } else {
        // Handle the case where magic_buffer returns NULL
        const char *error = magic_error(ms);
        if (error != NULL) {
            // std::cerr << "Magic error: " << error << std::endl;
        }
    }

    // Clean up
    magic_close(ms);

    return 0;
}