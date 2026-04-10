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
#include <stdlib.h>
#include "janet.h"

static void test_janet_rng_seed(JanetRNG *rng, const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint32_t)) {
        uint32_t seed = *((uint32_t *)Data);
        janet_rng_seed(rng, seed);
    }
}

static void test_janet_rng_u32(JanetRNG *rng) {
    uint32_t random_value = janet_rng_u32(rng);
    (void)random_value; // Suppress unused variable warning
}

static void test_janet_rng_longseed(JanetRNG *rng, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        janet_rng_longseed(rng, Data, (int32_t)Size);
    }
}

static void test_janet_rng_double(JanetRNG *rng) {
    double random_double = janet_rng_double(rng);
    (void)random_double; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_646(const uint8_t *Data, size_t Size) {
    JanetRNG rng;
    JanetRNG *default_rng = janet_default_rng();

    // Test janet_rng_seed
    test_janet_rng_seed(&rng, Data, Size);

    // Test janet_rng_u32
    test_janet_rng_u32(&rng);
    test_janet_rng_u32(default_rng);

    // Test janet_rng_longseed
    test_janet_rng_longseed(&rng, Data, Size);

    // Test janet_rng_double
    test_janet_rng_double(&rng);
    test_janet_rng_double(default_rng);

    return 0;
}