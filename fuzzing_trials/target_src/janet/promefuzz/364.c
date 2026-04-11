// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_wrap_number_safe at janet.c:37674:7 in janet.h
// janet_getnumber at janet.c:4511:1 in janet.h
// janet_optnumber at janet.c:4526:1 in janet.h
// janet_optnumber at janet.c:4526:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static double extract_double(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0.0;
    }
    double value;
    memcpy(&value, Data, sizeof(double));
    return value;
}

int LLVMFuzzerTestOneInput_364(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    // Initialize Janet VM
    janet_init();

    double number = extract_double(Data, Size);

    // Test janet_wrap_number
    Janet wrapped_number = janet_wrap_number(number);

    // Test janet_nanbox_from_double
    Janet nanboxed_number = janet_nanbox_from_double(number);

    // Test janet_wrap_number_safe
    Janet wrapped_number_safe = janet_wrap_number_safe(number);

    // Prepare Janet array for janet_getnumber and janet_optnumber
    Janet argv[3];
    argv[0] = wrapped_number;
    argv[1] = nanboxed_number;
    argv[2] = wrapped_number_safe;

    // Test janet_getnumber
    if (janet_checktype(argv[0], JANET_NUMBER)) {
        double retrieved_number = janet_getnumber(argv, 0);
    }

    // Test janet_optnumber with a valid index
    if (janet_checktype(argv[1], JANET_NUMBER)) {
        double optional_number_valid = janet_optnumber(argv, 3, 1, 0.0);
    }

    // Test janet_optnumber with an out-of-bounds index
    double optional_number_invalid = janet_optnumber(argv, 3, 5, 0.0);

    // Test janet_unwrap_number
    if (janet_checktype(wrapped_number, JANET_NUMBER)) {
        double unwrapped_number = janet_unwrap_number(wrapped_number);
    }

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}