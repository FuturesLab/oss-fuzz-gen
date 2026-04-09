// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_tuple_begin at tuple.c:34:8 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_compare at value.c:371:5 in janet.h
// janet_checkint16 at janet.c:34549:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_hash at value.c:309:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static Janet create_janet_from_data(const uint8_t *Data, size_t Size) {
    Janet janet_value;
    if (Size >= sizeof(double)) {
        janet_value.number = *(double *)Data;
    } else if (Size >= sizeof(int64_t)) {
        janet_value.i64 = *(int64_t *)Data;
    } else if (Size >= sizeof(uint64_t)) {
        janet_value.u64 = *(uint64_t *)Data;
    } else {
        janet_value.pointer = NULL;
    }
    return janet_value;
}

static int is_valid_janet_type(Janet x) {
    // Check if the Janet value is of a type that is safe to operate on
    // For simplicity, assume numbers and non-null pointers are valid
    return x.pointer != NULL || x.number != 0.0;
}

int LLVMFuzzerTestOneInput_741(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    janet_init();

    Janet janet_value1 = create_janet_from_data(Data, Size);
    Janet janet_value2 = create_janet_from_data(Data + (Size / 2), Size / 2);

    janet_checkint(janet_value1);
    janet_checkint16(janet_value1);

    int32_t length = (int32_t)(Data[0] % 128); // ensure non-negative length
    Janet *tuple = janet_tuple_begin(length);

    // Ensure both Janet values are valid and of compatible types before comparing
    if (is_valid_janet_type(janet_value1) && is_valid_janet_type(janet_value2) &&
        (janet_checkint(janet_value1) || janet_checkint16(janet_value1)) &&
        (janet_checkint(janet_value2) || janet_checkint16(janet_value2))) {
        janet_compare(janet_value1, janet_value2);
    }

    // Ensure the Janet value is valid for hashing
    if (janet_checkint(janet_value1) || janet_checkint16(janet_value1)) {
        janet_hash(janet_value1);
    }

    janet_deinit();

    return 0;
}