// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_getnumber at janet.c:4511:1 in janet.h
// janet_scan_number_base at strtod.c:252:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_wrap_number_safe at janet.c:37674:7 in janet.h
// janet_optnumber at janet.c:4526:1 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_getnumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;
    
    const Janet *argv = (const Janet *)Data;
    int32_t n = *(int32_t *)(Data + sizeof(Janet));
    
    if (n >= 0 && n < 1 && argv[0].number == argv[0].number) { // Check for valid number
        double result = janet_getnumber(argv, n);
        (void)result; // Use the result or assert its properties
    }
}

static void fuzz_janet_scan_number_base(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 2 + sizeof(double)) return;

    const uint8_t *str = Data;
    int32_t len = *(int32_t *)(Data + Size - sizeof(int32_t) * 2);
    int32_t base = *(int32_t *)(Data + Size - sizeof(int32_t));
    double out;

    if (len >= 0 && len <= Size && base >= 2 && base <= 36) {
        int result = janet_scan_number_base(str, len, base, &out);
        (void)result; // Use the result or assert its properties
    }
}

static void fuzz_janet_nanbox_from_double(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    double d = *(double *)Data;
    Janet result = janet_nanbox_from_double(d);
    (void)result; // Use the result or assert its properties
}

static void fuzz_janet_wrap_number_safe(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    double x = *(double *)Data;
    Janet result = janet_wrap_number_safe(x);
    (void)result; // Use the result or assert its properties
}

static void fuzz_janet_optnumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 3 + sizeof(double) + sizeof(int32_t)) return;

    const Janet *argv = (const Janet *)Data;
    int32_t argc = 3;
    int32_t n = *(int32_t *)(Data + sizeof(Janet) * 3);
    double dflt = *(double *)(Data + sizeof(Janet) * 3 + sizeof(int32_t));

    if (n >= 0 && n < argc && argv[n].number == argv[n].number) { // Check for valid number
        double result = janet_optnumber(argv, argc, n, dflt);
        (void)result; // Use the result or assert its properties
    }
}

static void fuzz_janet_unwrap_number(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;

    Janet x = *(Janet *)Data;
    if (x.number == x.number) { // Check if x is a number
        double result = janet_unwrap_number(x);
        (void)result; // Use the result or assert its properties
    }
}

int LLVMFuzzerTestOneInput_794(const uint8_t *Data, size_t Size) {
    fuzz_janet_getnumber(Data, Size);
    fuzz_janet_scan_number_base(Data, Size);
    fuzz_janet_nanbox_from_double(Data, Size);
    fuzz_janet_wrap_number_safe(Data, Size);
    fuzz_janet_optnumber(Data, Size);
    fuzz_janet_unwrap_number(Data, Size);
    return 0;
}