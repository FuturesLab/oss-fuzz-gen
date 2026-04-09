// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_checkuint16 at janet.c:34556:5 in janet.h
// janet_checkint64 at janet.c:34535:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_checkint64 at janet.c:34535:5 in janet.h
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
#include <stddef.h>
#include <stdint.h>
#include "janet.h"

static Janet create_janet_from_data(const uint8_t *data, size_t size) {
    Janet x;
    if (size >= sizeof(uint64_t)) {
        x.u64 = *(uint64_t *)data;
    } else if (size >= sizeof(int64_t)) {
        x.i64 = *(int64_t *)data;
    } else if (size >= sizeof(double)) {
        x.number = *(double *)data;
    } else {
        x.pointer = NULL; // Avoid using potentially invalid pointers
    }
    return x;
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    Janet x = create_janet_from_data(Data, Size);

    // Fuzz janet_checkuint16
    int result_uint16 = janet_checkuint16(x);

    // Fuzz janet_checkint64
    int result_int64 = janet_checkint64(x);

    // Fuzz janet_checkint
    int result_int = janet_checkint(x);

    // Fuzz janet_checkint16
    int result_int16 = janet_checkint16(x);

    // Only hash if the value is of a hashable type
    if (janet_checkint(x) || janet_checkint64(x) || janet_checkuint16(x) || janet_checkuint64(x)) {
        int32_t hash_result = janet_hash(x);
        (void)hash_result;
    }

    // Fuzz janet_checkuint64
    int result_uint64 = janet_checkuint64(x);

    // Use results to avoid unused variable warnings
    (void)result_uint16;
    (void)result_int64;
    (void)result_int;
    (void)result_int16;
    (void)result_uint64;

    return 0;
}