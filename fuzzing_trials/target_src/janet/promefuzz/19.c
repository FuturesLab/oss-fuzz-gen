// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_rng_seed at janet.c:20193:6 in janet.h
// janet_rng_u32 at janet.c:20217:10 in janet.h
// janet_rng_longseed at janet.c:20203:6 in janet.h
// janet_rng_double at janet.c:20232:8 in janet.h
// janet_default_rng at janet.c:20189:11 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_rng_seed(JanetRNG *rng, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return;
    uint32_t seed;
    memcpy(&seed, Data, sizeof(uint32_t));
    janet_rng_seed(rng, seed);
}

static void fuzz_janet_rng_u32(JanetRNG *rng) {
    uint32_t random_value = janet_rng_u32(rng);
    (void)random_value; // Use this value as needed for further fuzzing
}

static void fuzz_janet_rng_longseed(JanetRNG *rng, const uint8_t *Data, size_t Size) {
    janet_rng_longseed(rng, Data, (int32_t)Size);
}

static void fuzz_janet_rng_double(JanetRNG *rng) {
    double random_double = janet_rng_double(rng);
    (void)random_double; // Use this value as needed for further fuzzing
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    JanetRNG rng;
    JanetRNG *default_rng = janet_default_rng();

    // Fuzz janet_rng_seed
    fuzz_janet_rng_seed(&rng, Data, Size);

    // Fuzz janet_rng_u32
    fuzz_janet_rng_u32(&rng);
    fuzz_janet_rng_u32(default_rng);

    // Fuzz janet_rng_longseed
    fuzz_janet_rng_longseed(&rng, Data, Size);

    // Fuzz janet_rng_double
    fuzz_janet_rng_double(&rng);
    fuzz_janet_rng_double(default_rng);

    return 0;
}