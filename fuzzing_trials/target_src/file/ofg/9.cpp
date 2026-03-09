#include <stdint.h>
#include <stddef.h>
#include <magic.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    // Function signatures from the project-under-test
    struct magic_set *magic_open(int flags);
    int magic_load(struct magic_set *ms, const char *filename);
    const char *magic_buffer(struct magic_set *ms, const void *buffer, size_t length);
    void magic_close(struct magic_set *ms);
    const char *magic_error(struct magic_set *ms);
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Initialize a magic_set pointer
    struct magic_set *magic = magic_open(MAGIC_NONE);
    
    // Check if magic_set is initialized properly
    if (magic == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        // Print the error message for debugging purposes
        const char *error = magic_error(magic);
        if (error != NULL) {
            fprintf(stderr, "Magic load error: %s\n", error);
        }
        magic_close(magic);
        return 0;
    }

    // Ensure the data is not null and has a reasonable size
    if (data != NULL && size > 0) {
        // Use the data as input to magic_buffer to test its functionality
        const char *result = magic_buffer(magic, data, size);
        
        // Check the result to ensure the function is being used effectively
        if (result != NULL) {
            // Optionally, perform some operation with the result to ensure it's being processed
            printf("Magic result: %s\n", result); // Uncomment for debugging purposes
        }
    }

    // Call the function-under-test
    magic_close(magic);

    return 0;
}