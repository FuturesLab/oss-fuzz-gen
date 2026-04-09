#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// Function-under-test
void janet_sfree(void *ptr);

// Signal handler to catch abort signals
void handle_abort_212(int sig) {
    // Handle the abort signal, possibly logging or cleaning up
    exit(1);
}

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Register the signal handler for SIGABRT
    signal(SIGABRT, handle_abort_212);

    // Ensure the size is non-zero to avoid allocating zero bytes
    if (size == 0) {
        return 0;
    }

    // Allocate memory and copy the fuzz data into it
    void *buffer = malloc(size);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the data into the allocated buffer
    memcpy(buffer, data, size);

    // Call the function-under-test with the allocated buffer
    janet_sfree(buffer);

    // To maximize fuzzing result, call janet_sfree again with various inputs
    // Call with a null pointer
    janet_sfree(NULL);

    // Call with a small buffer
    void *small_buffer = malloc(1);
    if (small_buffer != NULL) {
        // Fill the small buffer with non-zero data
        memset(small_buffer, 0xFF, 1);
        janet_sfree(small_buffer);
        free(small_buffer);
    }

    // Call with a larger buffer
    void *large_buffer = malloc(1024);
    if (large_buffer != NULL) {
        // Fill the large buffer with non-zero data
        memset(large_buffer, 0xFF, 1024);
        janet_sfree(large_buffer);
        free(large_buffer);
    }

    // Free the allocated memory
    free(buffer);

    return 0;
}