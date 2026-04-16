#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

extern double janet_rng_double(JanetRNG *);

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetRNG)) {
        return 0;
    }

    // Initialize a JanetRNG object using the provided data
    JanetRNG rng;
    memcpy(&rng, data, sizeof(JanetRNG));

    // Call the function-under-test
    double result = janet_rng_double(&rng);

    // Use the result in some way to avoid compiler optimizations (dummy usage)
    if (result == 0.0) {
        return 0;
    }

    return 0;
}