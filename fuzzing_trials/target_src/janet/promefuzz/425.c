// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_optstruct at janet.c:4528:1 in janet.h
// janet_struct_find at janet.c:32513:16 in janet.h
// janet_struct_rawget at janet.c:32626:7 in janet.h
// janet_getstruct at janet.c:4515:1 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetStruct create_dummy_struct() {
    static JanetKV kvs[2] = {
        { .key = { .i64 = 1 }, .value = { .i64 = 100 } },
        { .key = { .i64 = 2 }, .value = { .i64 = 200 } }
    };
    return kvs;
}

static Janet create_dummy_janet() {
    Janet j;
    j.pointer = (void *)create_dummy_struct();
    return j;
}

int LLVMFuzzerTestOneInput_425(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2) return 0;

    int32_t index = *((int32_t *)Data);
    int32_t argc = *((int32_t *)(Data + sizeof(int32_t)));
    JanetStruct default_struct = create_dummy_struct();
    JanetStruct target_struct = create_dummy_struct();
    Janet key = create_dummy_janet();

    // Fuzz janet_wrap_struct
    Janet wrapped = janet_wrap_struct(target_struct);

    // Fuzz janet_optstruct
    Janet *argv = malloc(argc * sizeof(Janet));
    if (!argv) return 0;
    for (int i = 0; i < argc; i++) {
        argv[i] = create_dummy_janet();
    }
    JanetStruct opt_struct = janet_optstruct(argv, argc, index, default_struct);
    free(argv);

    // Fuzz janet_struct_find
    const JanetKV *found_kv = janet_struct_find(target_struct, key);

    // Fuzz janet_struct_rawget
    Janet raw_value = janet_struct_rawget(target_struct, key);

    // Fuzz janet_getstruct
    if (argc > 0) {
        JanetStruct get_struct = janet_getstruct(argv, index % argc);
    }

    // Fuzz janet_unwrap_struct
    JanetStruct unwrap_struct = janet_unwrap_struct(wrapped);

    return 0;
}