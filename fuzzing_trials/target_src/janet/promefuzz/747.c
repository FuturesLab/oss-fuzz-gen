// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_tuple_end at tuple.c:44:14 in janet.h
// janet_opttuple at janet.c:4527:1 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_tuple_n at tuple.c:50:14 in janet.h
// janet_gettuple at janet.c:4513:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetTuple create_dummy_tuple(int32_t length) {
    JanetTupleHead *head = (JanetTupleHead *) malloc(sizeof(JanetTupleHead) + sizeof(Janet) * length);
    if (!head) return NULL;
    head->length = length;
    head->hash = 0;
    head->sm_line = 0;
    head->sm_column = 0;
    Janet *data = (Janet *)head->data;
    for (int32_t i = 0; i < length; i++) {
        data[i].u64 = 0;
    }
    return (JanetTuple) head->data;
}

static void free_dummy_tuple(JanetTuple tuple) {
    if (tuple) {
        free((void *)((uintptr_t)tuple - offsetof(JanetTupleHead, data)));
    }
}

int LLVMFuzzerTestOneInput_747(const uint8_t *Data, size_t Size) {
    // Initialize Janet VM
    janet_init();

    if (Size < sizeof(int32_t) * 4) {
        janet_deinit();
        return 0;
    }

    int32_t tuple_length = ((int32_t *)Data)[0];
    int32_t argc = ((int32_t *)Data)[1];
    int32_t index = ((int32_t *)Data)[2];
    int32_t n = ((int32_t *)Data)[3];

    if (tuple_length < 0 || argc < 0 || n < 0 || Size < sizeof(int32_t) * 4 + sizeof(Janet) * (argc > n ? argc : n)) {
        janet_deinit();
        return 0;
    }

    const Janet *argv = (const Janet *)(Data + sizeof(int32_t) * 4);
    JanetTuple dflt = create_dummy_tuple(tuple_length);

    JanetTuple tuple = janet_tuple_end((Janet *)dflt);
    janet_opttuple(argv, argc, index, dflt);
    janet_wrap_tuple(tuple);
    if (tuple_length > 0) {
        janet_tuple_head(tuple);
    }
    janet_tuple_n(argv, n);
    if (argc > index) {
        janet_gettuple(argv, index);
    }

    free_dummy_tuple(dflt);

    // Deinitialize Janet VM
    janet_deinit();
    return 0;
}