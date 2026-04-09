// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_deinit at vm.c:1732:6 in janet.h
// janet_array_weak at janet.c:1569:13 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_array_setcount at janet.c:1606:6 in janet.h
// janet_optarray at janet.c:4540:1 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_array_ensure at janet.c:1589:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_array_ensure(JanetArray *array, int32_t capacity, int32_t growth) {
    janet_array_ensure(array, capacity, growth);
}

static void fuzz_janet_array_weak(int32_t capacity) {
    JanetArray *array = janet_array_weak(capacity);
    if (array) {
        // Do not free array, as it is managed by Janet's GC
    }
}

static void fuzz_janet_array(int32_t capacity) {
    JanetArray *array = janet_array(capacity);
    if (array) {
        // Do not free array, as it is managed by Janet's GC
    }
}

static void fuzz_janet_getarray(const Janet *argv, int32_t n) {
    JanetArray *array = janet_getarray(argv, n);
    if (array) {
        // Use the array in some way
    }
}

static void fuzz_janet_array_setcount(JanetArray *array, int32_t count) {
    janet_array_setcount(array, count);
}

static void fuzz_janet_optarray(const Janet *argv, int32_t argc, int32_t n, int32_t dflt_len) {
    JanetArray *array = janet_optarray(argv, argc, n, dflt_len);
    if (array) {
        // Use the array in some way
    }
}

int LLVMFuzzerTestOneInput_412(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    // Initialize Janet VM before using any Janet functions
    janet_init();

    int32_t capacity = *((int32_t *)Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetArray *array = janet_array(capacity);
    if (!array) {
        janet_deinit();
        return 0;
    }

    if (Size >= sizeof(int32_t)) {
        int32_t growth = *((int32_t *)Data);
        Data += sizeof(int32_t);
        Size -= sizeof(int32_t);
        fuzz_janet_array_ensure(array, capacity, growth);
    }

    if (Size >= sizeof(int32_t)) {
        int32_t count = *((int32_t *)Data);
        Data += sizeof(int32_t);
        Size -= sizeof(int32_t);
        fuzz_janet_array_setcount(array, count);
    }

    if (Size >= sizeof(int32_t)) {
        int32_t weak_capacity = *((int32_t *)Data);
        Data += sizeof(int32_t);
        Size -= sizeof(int32_t);
        fuzz_janet_array_weak(weak_capacity);
    }

    if (Size >= sizeof(int32_t)) {
        int32_t n = *((int32_t *)Data);
        Data += sizeof(int32_t);
        Size -= sizeof(int32_t);
        Janet argv[1] = {{.pointer = array}};
        fuzz_janet_getarray(argv, n);
    }

    if (Size >= sizeof(int32_t) * 3) {
        int32_t argc = *((int32_t *)Data);
        Data += sizeof(int32_t);
        int32_t opt_n = *((int32_t *)Data);
        Data += sizeof(int32_t);
        int32_t dflt_len = *((int32_t *)Data);
        Data += sizeof(int32_t);
        Janet opt_argv[1] = {{.pointer = array}};
        fuzz_janet_optarray(opt_argv, argc, opt_n, dflt_len);
    }

    // Do not free array, as it is managed by Janet's GC

    // Deinitialize Janet VM after all operations
    janet_deinit();

    return 0;
}