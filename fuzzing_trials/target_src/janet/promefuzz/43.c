// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_checkint64 at janet.c:34535:5 in janet.h
// janet_checkint64 at janet.c:34535:5 in janet.h
// janet_is_int at inttypes.c:172:14 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_checkint64 at janet.c:34535:5 in janet.h
// janet_hash at value.c:309:9 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_checkint64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    int result = janet_checkint64(x);
}

static void fuzz_janet_is_int(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    /* Ensure the Janet value is initialized properly */
    if (janet_checkint64(x)) {
        JanetIntType type = janet_is_int(x);
    }
}

static void fuzz_janet_wrap_boolean(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int x;
    memcpy(&x, Data, sizeof(int));
    Janet result = janet_wrap_boolean(x);
}

static void fuzz_janet_unwrap_boolean(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    /* Ensure the Janet value is a boolean */
    if (janet_wrap_boolean(0).u64 == x.u64 || janet_wrap_boolean(1).u64 == x.u64) {
        int result = janet_unwrap_boolean(x);
    }
}

static void fuzz_janet_hash(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    /* Ensure the Janet value is hashable */
    if (janet_checkint64(x) || janet_wrap_boolean(0).u64 == x.u64 || janet_wrap_boolean(1).u64 == x.u64) {
        int32_t hash = janet_hash(x);
    }
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    fuzz_janet_checkint64(Data, Size);
    fuzz_janet_is_int(Data, Size);
    fuzz_janet_wrap_boolean(Data, Size);
    fuzz_janet_unwrap_boolean(Data, Size);
    fuzz_janet_hash(Data, Size);
    return 0;
}