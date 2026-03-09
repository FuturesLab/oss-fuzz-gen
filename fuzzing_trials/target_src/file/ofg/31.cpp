#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize a magic_set object
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // Return if magic_open fails
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0; // Return if magic_load fails
    }

    // Ensure the data is not empty to maximize fuzzing effectiveness
    if (size == 0) {
        magic_close(magic);
        return 0; // Return if input size is zero
    }

    // Call the function-under-test
    const char *result = magic_buffer(magic, data, size);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // For example, we can print the result or just use it in a dummy operation
        volatile const char *dummy = result;
        (void)dummy;
    } else {
        // Handle the case where result is NULL to ensure code coverage
        const char *error = magic_error(magic);
        if (error != NULL) {
            volatile const char *dummy_error = error;
            (void)dummy_error;
        }
    }

    // Clean up
    magic_close(magic);

    return 0;
}