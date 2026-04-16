// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_scan_int64 at strtod.c:466:5 in janet.h
// janet_scan_uint64 at strtod.c:486:5 in janet.h
// janet_scan_number_base at strtod.c:252:5 in janet.h
// janet_scan_numeric at strtod.c:500:5 in janet.h
// janet_scan_number at strtod.c:395:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "janet.h"

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        atexit(janet_deinit);
        initialized = 1;
    }
}

static void fuzz_janet_scan_int64(const uint8_t *Data, size_t Size) {
    int64_t out;
    int result = janet_scan_int64(Data, (int32_t)Size, &out);
    if (result == 1) {
        // Successfully parsed int64_t
    } else {
        // Failed to parse
    }
}

static void fuzz_janet_scan_uint64(const uint8_t *Data, size_t Size) {
    uint64_t out;
    int result = janet_scan_uint64(Data, (int32_t)Size, &out);
    if (result == 1) {
        // Successfully parsed uint64_t
    } else {
        // Failed to parse
    }
}

static void fuzz_janet_scan_number_base(const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Need at least one byte for base
    int32_t base = Data[0] % 36 + 1; // Base can be from 1 to 36
    double out;
    int result = janet_scan_number_base(Data + 1, (int32_t)(Size - 1), base, &out);
    if (result == 1) {
        // Successfully parsed number with base
    } else {
        // Failed to parse
    }
}

static void fuzz_janet_scan_numeric(const uint8_t *Data, size_t Size) {
    Janet out;
    int result = janet_scan_numeric(Data, (int32_t)Size, &out);
    if (result == 1) {
        // Successfully parsed Janet number
    } else {
        // Failed to parse
    }
}

static void fuzz_janet_scan_number(const uint8_t *Data, size_t Size) {
    double out;
    int result = janet_scan_number(Data, (int32_t)Size, &out);
    if (result == 1) {
        // Successfully parsed double
    } else {
        // Failed to parse
    }
}

int LLVMFuzzerTestOneInput_680(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_scan_int64(Data, Size);
    fuzz_janet_scan_uint64(Data, Size);
    fuzz_janet_scan_number_base(Data, Size);
    fuzz_janet_scan_numeric(Data, Size);
    fuzz_janet_scan_number(Data, Size);
    return 0;
}