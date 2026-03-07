#include <stdint.h>
#include <stddef.h>
#include <magic.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    // Function signature from the project-under-test
    int magic_errno(struct magic_set *);
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Load magic data from the default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;
    }

    // Ensure the input data is not empty
    if (size == 0) {
        magic_close(ms);
        return 0;
    }

    // Here, we assume the input data is a string, so we null-terminate it
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        magic_close(ms);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Use the input to invoke another function that might trigger magic_errno
    const char *result = magic_buffer(ms, input, size);
    if (result == NULL) {
        int error_code = magic_errno(ms);  // Now, this might return a meaningful error code
        // Log or use the error_code for further analysis
        // For example, simulate different error handling paths
    } else {
        // Use result if needed, for example, logging or further processing
        // Simulate processing the result to increase code coverage
        // Process the result to simulate realistic usage
        if (strcmp(result, "text/plain") == 0) {
            // Simulate handling plain text files
        } else if (strcmp(result, "application/octet-stream") == 0) {
            // Simulate handling binary files
        }
        // Additional processing paths can be added here
    }

    // Clean up
    free(input);
    magic_close(ms);

    return 0;
}