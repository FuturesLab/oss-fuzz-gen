// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_checkuint16 at janet.c:34556:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_checkuint64 at janet.c:34542:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

// Helper function to create a Janet value from raw data
static Janet create_janet_value(const uint8_t *Data, size_t Size) {
    Janet x;
    if (Size >= sizeof(uint64_t)) {
        x.u64 = *((uint64_t *)Data);
    } else if (Size >= sizeof(int64_t)) {
        x.i64 = *((int64_t *)Data);
    } else if (Size >= sizeof(double)) {
        x.number = *((double *)Data);
    } else {
        x.pointer = (void *)Data;
    }
    return x;
}

int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a Janet value from the input data
    Janet x = create_janet_value(Data, Size);

    // Fuzz janet_checkuint16
    int result_uint16 = janet_checkuint16(x);

    // Fuzz janet_checkint
    int result_int = janet_checkint(x);

    // Fuzz janet_checkint16
    int result_int16 = janet_checkint16(x);

    // Fuzz janet_checkuint64
    int result_uint64 = janet_checkuint64(x);

    // Fuzz janet_wrap_integer with a random int32_t value
    if (Size >= sizeof(int32_t)) {
        int32_t int_val = *((int32_t *)Data);
        Janet wrapped = janet_wrap_integer(int_val);

        // Fuzz janet_unwrap_integer
        int32_t unwrapped = janet_unwrap_integer(wrapped);
    }

    return 0;
}