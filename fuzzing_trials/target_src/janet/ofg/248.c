#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// Function-under-test declaration
void janet_fixarity(int32_t expected, int32_t actual);

// Signal handler to catch abort signals and prevent crashes during fuzzing
void handle_abort_248(int sig) {
    (void)sig; // Suppress unused parameter warning
    exit(0);
}

int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two int32_t values
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Extract two int32_t values from the input data
    int32_t expected;
    int32_t actual;

    // Use memcpy to safely extract int32_t values, avoiding alignment issues
    memcpy(&expected, data, sizeof(int32_t));
    memcpy(&actual, data + sizeof(int32_t), sizeof(int32_t));

    // Register signal handler for abort signals
    signal(SIGABRT, handle_abort_248);

    // Ensure that the function-under-test is called with diverse inputs
    // by avoiding trivial cases such as both values being zero
    if (expected == 0 && actual == 0) {
        expected = 1; // Change one value to avoid trivial case
    }

    // Call the function-under-test with the extracted values
    janet_fixarity(expected, actual);

    return 0;
}