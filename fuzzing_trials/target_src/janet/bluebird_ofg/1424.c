#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include "janet.h" // Assuming JanetRNG is defined in this header

int LLVMFuzzerTestOneInput_1424(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to initialize a JanetRNG
    if (size < sizeof(JanetRNG)) {
        return 0;
    }

    // Create and initialize a JanetRNG object
    JanetRNG rng;
    // Copy the data into the JanetRNG object for initialization
    // Assuming JanetRNG can be initialized with raw bytes
    memcpy(&rng, data, sizeof(JanetRNG));

    // Call the function-under-test
    double result = janet_rng_double(&rng);

    // Use the result in some way to prevent compiler optimizations from removing the call
    volatile double use_result = result;
    (void)use_result;

    return 0;
}