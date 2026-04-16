// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_length at value.c:641:9 in janet.h
// janet_length at value.c:641:9 in janet.h
// janet_in at value.c:453:7 in janet.h
// janet_equals at value.c:249:5 in janet.h
// janet_length at value.c:641:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static Janet generate_random_janet(const uint8_t **Data, size_t *Size) {
    if (*Size < 1) return janet_wrap_nil();
    JanetType type = (JanetType)((*Data)[0] % 16);
    (*Data)++;
    (*Size)--;

    switch (type) {
        case JANET_NIL:
            return janet_wrap_nil();
        case JANET_BOOLEAN:
            if (*Size < 1) return janet_wrap_nil();
            Janet b = janet_wrap_boolean((*Data)[0] % 2);
            (*Data)++;
            (*Size)--;
            return b;
        case JANET_NUMBER:
            if (*Size < sizeof(double)) return janet_wrap_nil();
            double num;
            memcpy(&num, *Data, sizeof(double));
            (*Data) += sizeof(double);
            (*Size) -= sizeof(double);
            return janet_wrap_number(num);
        case JANET_STRING:
        case JANET_SYMBOL:
        case JANET_KEYWORD:
        case JANET_BUFFER:
        {
            if (*Size < 1) return janet_wrap_nil();
            size_t len = (*Data)[0] % (*Size);
            (*Data)++;
            (*Size)--;
            if (len > *Size) len = *Size;
            Janet str = janet_stringv(*Data, len);
            (*Data) += len;
            (*Size) -= len;
            return str;
        }
        default:
            return janet_wrap_nil();
    }
}

int LLVMFuzzerTestOneInput_768(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure Janet is initialized before use
    janet_init();

    Janet ds = generate_random_janet(&Data, &Size);
    Janet key = generate_random_janet(&Data, &Size);
    Janet x = generate_random_janet(&Data, &Size);
    Janet y = generate_random_janet(&Data, &Size);

    // Test janet_in with proper checks
    if ((janet_checktype(ds, JANET_ARRAY) || janet_checktype(ds, JANET_TABLE) || janet_checktype(ds, JANET_STRUCT)) &&
        janet_checktype(key, JANET_NUMBER) &&
        janet_length(ds) > 0 &&
        janet_unwrap_number(key) >= 0 &&
        janet_unwrap_number(key) < janet_length(ds)) {
        janet_in(ds, key);
    }

    // Test janet_equals
    janet_equals(x, y);

    // Test janet_type
    janet_type(x);

    // Test janet_length with valid types
    if (janet_checktype(x, JANET_STRING) || janet_checktype(x, JANET_ARRAY) || janet_checktype(x, JANET_BUFFER) || janet_checktype(x, JANET_TUPLE)) {
        janet_length(x);
    }

    // Test janet_checktype
    janet_checktype(x, janet_type(y));

    // Cleanup Janet environment
    janet_deinit();

    return 0;
}