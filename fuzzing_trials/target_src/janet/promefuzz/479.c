// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

static JanetStruct create_dummy_struct() {
    static JanetKV kv = { {0}, {0} };
    return &kv;
}

static JanetAbstract create_dummy_abstract() {
    static int dummy;
    return &dummy;
}

static JanetString create_dummy_string(const uint8_t *Data, size_t Size) {
    return (JanetString) Data;
}

static JanetKeyword create_dummy_keyword(const uint8_t *Data, size_t Size) {
    return (JanetKeyword) Data;
}

int LLVMFuzzerTestOneInput_479(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    // Fuzz janet_wrap_struct
    JanetStruct js = create_dummy_struct();
    Janet wrapped_struct = janet_wrap_struct(js);

    // Fuzz janet_wrap_abstract
    JanetAbstract ja = create_dummy_abstract();
    Janet wrapped_abstract = janet_wrap_abstract(ja);

    // Fuzz janet_wrap_integer
    int32_t integer = *(const int32_t *)Data;
    Janet wrapped_integer = janet_wrap_integer(integer);

    // Fuzz janet_wrap_string
    JanetString jstr = create_dummy_string(Data, Size);
    Janet wrapped_string = janet_wrap_string(jstr);

    // Fuzz janet_wrap_keyword
    JanetKeyword jkw = create_dummy_keyword(Data, Size);
    Janet wrapped_keyword = janet_wrap_keyword(jkw);

    return 0;
}