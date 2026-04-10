// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_tuple_n at tuple.c:50:14 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_tuple_end at tuple.c:44:14 in janet.h
// janet_opttuple at janet.c:4527:1 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_tuple_n at tuple.c:50:14 in janet.h
// janet_gettuple at janet.c:4513:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static JanetTuple create_dummy_tuple(int32_t length) {
    Janet *data = (Janet *)malloc(sizeof(Janet) * length);
    for (int32_t i = 0; i < length; i++) {
        data[i].u64 = (uint64_t)rand();
    }
    JanetTuple tuple = janet_tuple_n(data, length);
    free(data);
    return tuple;
}

static void clean_dummy_tuple(JanetTuple tuple) {
    // No need to free tuple as it's managed by Janet's GC
}

int LLVMFuzzerTestOneInput_662(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 3) return 0;

    // Initialize Janet VM
    janet_init();

    int32_t argc = ((int32_t *)Data)[0];
    int32_t n = ((int32_t *)Data)[1];
    int32_t length = ((int32_t *)Data)[2];
    Data += sizeof(int32_t) * 3;
    Size -= sizeof(int32_t) * 3;

    Janet *argv = (Janet *)malloc(sizeof(Janet) * argc);
    for (int32_t i = 0; i < argc && Size >= sizeof(Janet); i++) {
        memcpy(&argv[i], Data, sizeof(Janet));
        Data += sizeof(Janet);
        Size -= sizeof(Janet);
    }

    JanetTuple dummy_tuple = create_dummy_tuple(length);

    // Fuzz janet_tuple_end
    JanetTuple end_tuple = janet_tuple_end(dummy_tuple);

    // Fuzz janet_opttuple
    JanetTuple opt_tuple = janet_opttuple(argv, argc, n, dummy_tuple);

    // Fuzz janet_wrap_tuple
    Janet wrapped_tuple = janet_wrap_tuple(dummy_tuple);

    // Fuzz janet_tuple_head
    if (length > 0) {
        const Janet *head = janet_tuple_head(dummy_tuple);
    }

    // Fuzz janet_tuple_n
    JanetTuple new_tuple = janet_tuple_n(argv, argc);

    // Fuzz janet_gettuple
    if (n >= 0 && n < argc) {
        JanetTuple get_tuple = janet_gettuple(argv, n);
    }

    free(argv);
    clean_dummy_tuple(dummy_tuple);

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}