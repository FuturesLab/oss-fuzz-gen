// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_array_ensure at janet.c:1589:6 in janet.h
// janet_array_weak at janet.c:1569:13 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_array_setcount at janet.c:1606:6 in janet.h
// janet_optarray at janet.c:4540:1 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_array_ensure(JanetArray *array, int32_t capacity, int32_t growth) {
    if (array) {
        janet_array_ensure(array, capacity, growth);
    }
}

static JanetArray *fuzz_janet_array_weak(int32_t capacity) {
    return (capacity >= 0) ? janet_array_weak(capacity) : NULL;
}

static JanetArray *fuzz_janet_array(int32_t capacity) {
    return (capacity >= 0) ? janet_array(capacity) : NULL;
}

static JanetArray *fuzz_janet_getarray(const Janet *argv, int32_t n, int32_t argc) {
    return (n >= 0 && n < argc) ? janet_getarray(argv, n) : NULL;
}

static void fuzz_janet_array_setcount(JanetArray *array, int32_t count) {
    if (array && count >= 0) {
        janet_array_setcount(array, count);
    }
}

static JanetArray *fuzz_janet_optarray(const Janet *argv, int32_t argc, int32_t n, int32_t dflt_len) {
    return (n >= 0 && n < argc) ? janet_optarray(argv, argc, n, dflt_len) : NULL;
}

int LLVMFuzzerTestOneInput_463(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 4) return 0;

    janet_init();

    int32_t capacity = ((int32_t *)Data)[0];
    int32_t growth = ((int32_t *)Data)[1];
    int32_t count = ((int32_t *)Data)[2];
    int32_t index = ((int32_t *)Data)[3];

    // Fuzz janet_array
    JanetArray *array = fuzz_janet_array(capacity);
    if (!array) {
        janet_deinit();
        return 0;
    }

    // Fuzz janet_array_ensure
    fuzz_janet_array_ensure(array, capacity, growth);

    // Fuzz janet_array_setcount
    fuzz_janet_array_setcount(array, count);

    // Fuzz janet_array_weak
    JanetArray *weak_array = fuzz_janet_array_weak(capacity);
    if (weak_array) {
        fuzz_janet_array_setcount(weak_array, count);
    }

    // Prepare dummy Janet array for janet_getarray and janet_optarray
    Janet dummy_janet[2];
    dummy_janet[0].pointer = array;
    dummy_janet[1].pointer = weak_array;

    // Fuzz janet_getarray
    fuzz_janet_getarray(dummy_janet, index, 2);

    // Fuzz janet_optarray
    fuzz_janet_optarray(dummy_janet, 2, index, capacity);

    // Cleanup
    // Do not free array or weak_array manually, let janet_deinit handle it
    janet_deinit();

    return 0;
}