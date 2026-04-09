// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_getnumber at janet.c:4511:1 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_wrap_number_safe at janet.c:37674:7 in janet.h
// janet_optnumber at janet.c:4526:1 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static void fuzz_janet_wrap_number(double value) {
    Janet janet_value = janet_wrap_number(value);
    // Use janet_unwrap_number to verify the wrapping
    double unwrapped_value = janet_unwrap_number(janet_value);
    (void)unwrapped_value; // Suppress unused variable warning
}

static void fuzz_janet_getnumber(const Janet *argv, int32_t argc) {
    if (argc > 0) {
        int32_t index = rand() % argc;
        double number = janet_getnumber(argv, index);
        (void)number; // Suppress unused variable warning
    }
}

static void fuzz_janet_nanbox_from_double(double value) {
    Janet janet_value = janet_nanbox_from_double(value);
    // Use janet_unwrap_number to verify the conversion
    double unwrapped_value = janet_unwrap_number(janet_value);
    (void)unwrapped_value; // Suppress unused variable warning
}

static void fuzz_janet_wrap_number_safe(double value) {
    Janet janet_value = janet_wrap_number_safe(value);
    // Use janet_unwrap_number to verify the wrapping
    double unwrapped_value = janet_unwrap_number(janet_value);
    (void)unwrapped_value; // Suppress unused variable warning
}

static void fuzz_janet_optnumber(const Janet *argv, int32_t argc, double dflt) {
    if (argc >= 3) {
        int32_t index = rand() % argc;
        double number = janet_optnumber(argv, argc, index, dflt);
        (void)number; // Suppress unused variable warning
    }
}

int LLVMFuzzerTestOneInput_704(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    double value;
    memcpy(&value, Data, sizeof(double));

    Janet array[3];
    for (int i = 0; i < 3; i++) {
        array[i] = janet_wrap_number((double)i);
    }

    fuzz_janet_wrap_number(value);
    fuzz_janet_getnumber(array, 3);
    fuzz_janet_nanbox_from_double(value);
    fuzz_janet_wrap_number_safe(value);
    fuzz_janet_optnumber(array, 3, 0.0);

    return 0;
}