// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_to_string at janet.c:28692:16 in janet.h
// janet_wrap_s64 at inttypes.c:180:7 in janet.h
// janet_nanbox_from_cpointer at janet.c:37698:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static JanetString create_dummy_string(const uint8_t *data, size_t size) {
    uint8_t *str = (uint8_t *)malloc(size + 1);
    if (str) {
        memcpy(str, data, size);
        str[size] = '\0';
    }
    return str;
}

static JanetKeyword create_dummy_keyword(const uint8_t *data, size_t size) {
    return create_dummy_string(data, size);
}

int LLVMFuzzerTestOneInput_736(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    // Fuzz janet_wrap_string
    JanetString jstr = create_dummy_string(Data, Size);
    if (jstr) {
        Janet wrapped_string = janet_wrap_string(jstr);
        (void)wrapped_string;
        free((void *)jstr);
    }

    // Fuzz janet_to_string
    Janet dummy_value;
    dummy_value.pointer = (void *)Data;
    JanetString result_string = janet_to_string(dummy_value);
    (void)result_string;

    // Fuzz janet_wrap_s64
    if (Size >= sizeof(int64_t)) {
        int64_t value;
        memcpy(&value, Data, sizeof(int64_t));
        Janet wrapped_int = janet_wrap_s64(value);
        (void)wrapped_int;
    }

    // Fuzz janet_wrap_keyword
    JanetKeyword jkeyword = create_dummy_keyword(Data, Size);
    if (jkeyword) {
        Janet wrapped_keyword = janet_wrap_keyword(jkeyword);
        (void)wrapped_keyword;
        free((void *)jkeyword);
    }

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}