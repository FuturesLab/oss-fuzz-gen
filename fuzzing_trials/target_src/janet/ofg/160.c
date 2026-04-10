#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // Include standard library for abort function
#include "/src/janet/src/include/janet.h" // Correct path for Janet types and functions

// Function prototype for the fuzzer
int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a uint32_t value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t capacity = *((uint32_t *)data);

    // Check for a reasonable capacity to avoid potential issues
    if (capacity == 0 || capacity > 1000000) { // Arbitrary large value to prevent excessive allocation
        return 0;
    }

    // Call the function-under-test
    JanetChannel *channel = janet_channel_make(capacity);

    // Check if channel is successfully created
    if (channel == NULL) {
        return 0;
    }

    // Perform any necessary cleanup
    janet_gcroot(janet_wrap_pointer(channel));
    janet_gcunroot(janet_wrap_pointer(channel));

    return 0;
}