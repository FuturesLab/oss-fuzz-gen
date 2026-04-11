#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1323(const uint8_t *data, size_t size) {
    // Declare and initialize the JanetRNG structure
    JanetRNG rng;
    janet_rng_seed(&rng, 42); // Initialize with a non-zero seed

    // Ensure the data size is sufficient for the seed
    if (size < 4) {
        return 0;
    }

    // Call the function-under-test
    janet_rng_longseed(&rng, data, (int32_t)size);

    return 0;
}