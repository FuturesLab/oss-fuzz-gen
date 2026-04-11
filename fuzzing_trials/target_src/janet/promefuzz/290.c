// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_checkuint16 at janet.c:34556:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_tuple_begin at tuple.c:34:8 in janet.h
// janet_checkuint16 at janet.c:34556:5 in janet.h
// janet_checkuint64 at janet.c:34542:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_hash at value.c:309:9 in janet.h
// janet_checkuint64 at janet.c:34542:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_checkuint16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    janet_checkuint16(x);
}

static void fuzz_janet_wrap_integer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t x;
    memcpy(&x, Data, sizeof(int32_t));
    janet_wrap_integer(x);
}

static void fuzz_janet_checkint(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    janet_checkint(x);
}

static void fuzz_janet_tuple_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t length;
    memcpy(&length, Data, sizeof(int32_t));
    if (length < 0 || length > 1000) return; // Arbitrary sensible upper limit
    janet_init();
    Janet *tuple = janet_tuple_begin(length);
    (void)tuple; // Suppress unused variable warning
    // No manual free, handled by Janet GC
}

static void fuzz_janet_hash(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    // Ensure that the Janet value is a valid type for hashing
    if (janet_checkint(x) || janet_checkuint16(x) || janet_checkuint64(x)) {
        janet_hash(x);
    }
}

static void fuzz_janet_checkuint64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    janet_checkuint64(x);
}

int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size) {
    fuzz_janet_checkuint16(Data, Size);
    fuzz_janet_wrap_integer(Data, Size);
    fuzz_janet_checkint(Data, Size);
    fuzz_janet_tuple_begin(Data, Size);
    fuzz_janet_hash(Data, Size);
    fuzz_janet_checkuint64(Data, Size);
    return 0;
}