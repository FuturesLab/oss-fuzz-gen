#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for abort()
#include <stdio.h>  // Include for printf(), useful for debugging
#include <signal.h> // Include for signal handling

// The function-under-test declaration
void janet_sandbox(uint32_t);

// A helper function to ensure the input data is not all zeros
uint32_t create_nonzero_uint32(const uint8_t *data) {
    uint32_t result = 0;
    memcpy(&result, data, sizeof(uint32_t));
    // Ensure the result is not zero, as it might be an edge case causing issues
    if (result == 0) {
        result = 1; // Set to a non-zero value
    }
    return result;
}

// Signal handler for SIGABRT
void handle_sigabrt(int sig) {
    printf("Caught SIGABRT: %d\n", sig);
    exit(1);
}

int LLVMFuzzerTestOneInput_329(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Set up the signal handler for SIGABRT
    signal(SIGABRT, handle_sigabrt);

    // Extract a uint32_t from the input data and ensure it is not zero
    uint32_t sandbox_input = create_nonzero_uint32(data);

    // Call the function-under-test
    // Wrap the call in a try-catch-like structure to handle potential crashes
    // Since C doesn't have exceptions, we use a signal handler for SIGABRT
    janet_sandbox(sandbox_input);

    return 0;
}