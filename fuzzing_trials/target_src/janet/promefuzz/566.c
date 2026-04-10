// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static JanetStruct create_dummy_struct(const uint8_t *data, size_t size) {
    size_t num_kvs = size / sizeof(JanetKV);
    JanetKV *kvs = malloc(num_kvs * sizeof(JanetKV));
    for (size_t i = 0; i < num_kvs; i++) {
        kvs[i].key.u64 = (i < size) ? data[i] : 0;
        kvs[i].value.u64 = (i + 1 < size) ? data[i + 1] : 0;
    }
    return (JanetStruct)kvs;
}

static JanetKeyword create_dummy_keyword(const uint8_t *data, size_t size) {
    return (JanetKeyword)data;
}

static JanetAbstract create_dummy_abstract(const uint8_t *data, size_t size) {
    return (JanetAbstract)data;
}

static JanetString create_dummy_string(const uint8_t *data, size_t size) {
    return (JanetString)data;
}

static JanetSymbol create_dummy_symbol(const uint8_t *data, size_t size) {
    return (JanetSymbol)data;
}

int LLVMFuzzerTestOneInput_566(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    JanetStruct js = create_dummy_struct(Data, Size);
    JanetKeyword jk = create_dummy_keyword(Data, Size);
    JanetAbstract ja = create_dummy_abstract(Data, Size);
    JanetString jstr = create_dummy_string(Data, Size);
    JanetSymbol jsy = create_dummy_symbol(Data, Size);

    Janet result;
    result = janet_wrap_struct(js);
    result = janet_wrap_keyword(jk);
    result = janet_wrap_abstract(ja);
    result = janet_wrap_string(jstr);
    result = janet_wrap_symbol(jsy);

    free((void *)js);
    
    return 0;
}