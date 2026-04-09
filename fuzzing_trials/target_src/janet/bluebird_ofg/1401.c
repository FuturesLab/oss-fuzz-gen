#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>

// Function under test
void janet_sandbox(uint32_t);

// Signal handler to catch abort signals
void handle_abort(int sig) {
    // Handle the abort signal (e.g., log, clean up, etc.)
    // For fuzzing, we just want to prevent the program from terminating
}

// Fuzzing harness
int LLVMFuzzerTestOneInput_1401(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Register signal handler for abort signals
    signal(SIGABRT, handle_abort);

    // Extract a uint32_t from the input data
    uint32_t input_value = *(const uint32_t *)data;

    // Call the function under test
    janet_sandbox(input_value);

    return 0;
}