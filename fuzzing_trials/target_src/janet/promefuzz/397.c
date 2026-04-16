// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_array_ensure at janet.c:1589:6 in janet.h
// janet_array_weak at janet.c:1569:13 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_array_setcount at janet.c:1606:6 in janet.h
// janet_optarray at janet.c:4540:1 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_array_ensure(JanetArray *array, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    int32_t capacity = *((int32_t *) Data);
    int32_t growth = *((int32_t *) (Data + 4));
    janet_array_ensure(array, capacity, growth);
}

static void fuzz_janet_array_weak(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    int32_t capacity = *((int32_t *) Data);
    JanetArray *array = janet_array_weak(capacity);
    // Do something with the array if needed
}

static void fuzz_janet_array(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    int32_t capacity = *((int32_t *) Data);
    JanetArray *array = janet_array(capacity);
    // Do something with the array if needed
}

static void fuzz_janet_getarray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + 4) return;
    const Janet *argv = (const Janet *) Data;
    int32_t n = *((int32_t *) (Data + sizeof(Janet)));
    JanetArray *array = janet_getarray(argv, n);
    // Do something with the array if needed
}

static void fuzz_janet_array_setcount(JanetArray *array, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    int32_t count = *((int32_t *) Data);
    janet_array_setcount(array, count);
}

static void fuzz_janet_optarray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + 12) return;
    const Janet *argv = (const Janet *) Data;
    int32_t argc = *((int32_t *) (Data + sizeof(Janet)));
    int32_t n = *((int32_t *) (Data + sizeof(Janet) + 4));
    int32_t dflt_len = *((int32_t *) (Data + sizeof(Janet) + 8));
    JanetArray *array = janet_optarray(argv, argc, n, dflt_len);
    // Do something with the array if needed
}

int LLVMFuzzerTestOneInput_397(const uint8_t *Data, size_t Size) {
    // Initialize the Janet VM
    janet_init();

    JanetArray *array = janet_array(10); // Initial array for testing

    fuzz_janet_array_ensure(array, Data, Size);
    fuzz_janet_array_weak(Data, Size);
    fuzz_janet_array(Data, Size);
    fuzz_janet_getarray(Data, Size);
    fuzz_janet_array_setcount(array, Data, Size);
    fuzz_janet_optarray(Data, Size);

    // Cleanup
    janet_deinit();

    return 0;
}