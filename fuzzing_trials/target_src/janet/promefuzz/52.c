// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
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
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_wrap_number(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double num;
    memcpy(&num, Data, sizeof(double));
    Janet j = janet_wrap_number(num);
    (void)j; // Suppress unused variable warning
}

static void fuzz_janet_getnumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    Janet argv[1];
    memcpy(&argv[0].number, Data, sizeof(double));
    
    // Ensure the Janet value is a number before calling janet_getnumber
    if ((argv[0].u64 & 0x7FF0000000000000) != 0x7FF0000000000000) {
        double result = janet_getnumber(argv, 0);
        (void)result; // Suppress unused variable warning
    }
}

static void fuzz_janet_nanbox_from_double(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double num;
    memcpy(&num, Data, sizeof(double));
    Janet j = janet_nanbox_from_double(num);
    (void)j; // Suppress unused variable warning
}

static void fuzz_janet_wrap_number_safe(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double num;
    memcpy(&num, Data, sizeof(double));
    Janet j = janet_wrap_number_safe(num);
    (void)j; // Suppress unused variable warning
}

static void fuzz_janet_optnumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 3 + sizeof(double)) return;
    Janet argv[3];
    memcpy(&argv[0].number, Data, sizeof(double));
    memcpy(&argv[1].number, Data + sizeof(double), sizeof(double));
    memcpy(&argv[2].number, Data + 2 * sizeof(double), sizeof(double));
    double dflt;
    memcpy(&dflt, Data + 3 * sizeof(double), sizeof(double));
    
    // Ensure the index is valid and the value is a number
    if ((argv[1].u64 & 0x7FF0000000000000) != 0x7FF0000000000000) {
        double result = janet_optnumber(argv, 3, 1, dflt);
        (void)result; // Suppress unused variable warning
    }
}

static void fuzz_janet_unwrap_number(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double num;
    memcpy(&num, Data, sizeof(double));
    Janet j = janet_wrap_number(num);
    double result = janet_unwrap_number(j);
    (void)result; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_wrap_number(Data, Size);
    fuzz_janet_getnumber(Data, Size);
    fuzz_janet_nanbox_from_double(Data, Size);
    fuzz_janet_wrap_number_safe(Data, Size);
    fuzz_janet_optnumber(Data, Size);
    fuzz_janet_unwrap_number(Data, Size);
    return 0;
}