// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_current_fiber at fiber.c:446:13 in janet.h
// janet_current_fiber at fiber.c:446:13 in janet.h
// janet_sleep_await at janet.c:12093:22 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_current_fiber at fiber.c:446:13 in janet.h
// janet_current_fiber at fiber.c:446:13 in janet.h
// janet_addtimeout_nil at janet.c:9534:6 in janet.h
// janet_rng_double at janet.c:20232:8 in janet.h
// janet_wrap_number_safe at janet.c:37674:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "janet.h"

// Dummy function to simulate fiber environment
static void setup_dummy_fiber() {
    // This is a placeholder. In a real scenario, you would set up a Janet fiber environment.
}

static double get_double_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0.0;
    double value;
    memcpy(&value, Data, sizeof(double));
    return value;
}

static void fuzz_janet_sleep_await(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double seconds = get_double_from_data(Data, Size);
    if (seconds < 0) return; // Avoid negative sleep times

    setup_dummy_fiber(); // Ensure a fiber environment is set up
    // Check if the fiber and scheduler are properly initialized
    if (janet_current_fiber() && janet_current_fiber()->sched_id) {
        janet_sleep_await(seconds);
    }
}

static void fuzz_janet_wrap_number(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double x = get_double_from_data(Data, Size);
    Janet wrapped = janet_wrap_number(x);
    (void)wrapped; // Use wrapped to avoid unused variable warning
}

static void fuzz_janet_addtimeout_nil(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double seconds = get_double_from_data(Data, Size);
    if (seconds < 0) return; // Avoid negative timeout values

    setup_dummy_fiber(); // Ensure a fiber environment is set up
    // Check if the fiber and scheduler are properly initialized
    if (janet_current_fiber() && janet_current_fiber()->sched_id) {
        janet_addtimeout_nil(seconds);
    }
}

static void fuzz_janet_rng_double(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetRNG)) return;
    JanetRNG rng;
    memcpy(&rng, Data, sizeof(JanetRNG));
    double random_value = janet_rng_double(&rng);
    (void)random_value; // Use random_value to avoid unused variable warning
}

static void fuzz_janet_wrap_number_safe(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double x = get_double_from_data(Data, Size);
    Janet wrapped_safe = janet_wrap_number_safe(x);
    (void)wrapped_safe; // Use wrapped_safe to avoid unused variable warning
}

int LLVMFuzzerTestOneInput_448(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;
    
    fuzz_janet_sleep_await(Data, Size);
    fuzz_janet_wrap_number(Data, Size);
    fuzz_janet_addtimeout_nil(Data, Size);
    fuzz_janet_rng_double(Data, Size);
    fuzz_janet_wrap_number_safe(Data, Size);
    
    return 0;
}