#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include "janet.h" // Assuming this is the header file where JanetRNG and janet_rng_u32 are defined

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to initialize JanetRNG
    if (size < sizeof(JanetRNG)) {
        return 0;
    }

    // Initialize a JanetRNG structure from the input data
    JanetRNG rng;
    // Copy data into rng, ensuring we do not exceed the size of JanetRNG
    memcpy(&rng, data, sizeof(JanetRNG));

    // Call the function-under-test
    uint32_t result = janet_rng_u32(&rng);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}