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
#include <janet.h>

static void fuzz_janet_array_ensure(JanetArray *array, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return;
    int32_t capacity = ((int32_t *)Data)[0];
    int32_t growth = ((int32_t *)Data)[1];
    janet_array_ensure(array, capacity, growth);
}

static JanetArray *fuzz_janet_array_weak(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return NULL;
    int32_t capacity = ((int32_t *)Data)[0];
    return janet_array_weak(capacity);
}

static JanetArray *fuzz_janet_array(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return NULL;
    int32_t capacity = ((int32_t *)Data)[0];
    return janet_array(capacity);
}

static JanetArray *fuzz_janet_getarray(const Janet *argv, int32_t argc, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return NULL;
    int32_t n = ((int32_t *)Data)[0] % argc;
    return janet_getarray(argv, n);
}

static void fuzz_janet_array_setcount(JanetArray *array, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t count = ((int32_t *)Data)[0];
    janet_array_setcount(array, count);
}

static JanetArray *fuzz_janet_optarray(const Janet *argv, int32_t argc, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return NULL;
    int32_t n = ((int32_t *)Data)[0] % argc;
    int32_t dflt_len = ((int32_t *)Data)[1];
    return janet_optarray(argv, argc, n, dflt_len);
}

int LLVMFuzzerTestOneInput_223(const uint8_t *Data, size_t Size) {
    // Initialize the Janet runtime
    janet_init();

    JanetArray *array = fuzz_janet_array(Data, Size);
    if (!array) {
        janet_deinit();
        return 0;
    }

    fuzz_janet_array_ensure(array, Data, Size);
    fuzz_janet_array_setcount(array, Data, Size);

    JanetArray *weak_array = fuzz_janet_array_weak(Data, Size);
    if (weak_array) {
        fuzz_janet_array_ensure(weak_array, Data, Size);
        fuzz_janet_array_setcount(weak_array, Data, Size);
    }

    Janet argv[2] = {{.pointer = array}, {.pointer = weak_array}};
    int32_t argc = 2;
    JanetArray *retrieved_array = fuzz_janet_getarray(argv, argc, Data, Size);
    if (retrieved_array) {
        fuzz_janet_array_setcount(retrieved_array, Data, Size);
    }

    JanetArray *opt_array = fuzz_janet_optarray(argv, argc, Data, Size);
    if (opt_array) {
        fuzz_janet_array_setcount(opt_array, Data, Size);
    }

    // Deinitialize the Janet runtime
    janet_deinit();

    return 0;
}