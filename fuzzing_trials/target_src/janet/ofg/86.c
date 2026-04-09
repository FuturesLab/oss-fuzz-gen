#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h" // Assuming this is the header where JanetRNG is defined

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    JanetRNG rng;
    const uint8_t *seed_data;
    int32_t seed_size;

    // Ensure that seed_size is not greater than the actual data size
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Use the first 4 bytes of data as the seed size
    seed_size = (int32_t)(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

    // Ensure seed_size is non-negative and does not exceed the remaining data
    if (seed_size < 0 || (size - sizeof(int32_t)) < (size_t)seed_size) {
        return 0;
    }

    // Set seed_data to the remaining bytes after the seed size
    seed_data = data + sizeof(int32_t);

    // Call the function-under-test
    janet_rng_longseed(&rng, seed_data, seed_size);

    return 0;
}