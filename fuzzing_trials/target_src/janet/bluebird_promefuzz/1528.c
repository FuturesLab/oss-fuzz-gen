#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_scan_number_base(const uint8_t *data, size_t size) {
    if (size < 1) {
        return;
    }

    double out;
    int32_t base = (data[0] % 36) + 1; // base between 1 and 36
    janet_scan_number_base(data + 1, size - 1, base, &out);
}

static void fuzz_scan_uint64(const uint8_t *data, size_t size) {
    if (size < 1) {
        return;
    }

    uint64_t out;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of janet_scan_uint64
    janet_scan_uint64(data, JANET_SANDBOX_DYNAMIC_MODULES, &out);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static void fuzz_scan_numeric(const uint8_t *data, size_t size) {
    if (size < 1) {
        return;
    }

    Janet out;
    janet_scan_numeric(data, (int32_t)size, &out);
}

int LLVMFuzzerTestOneInput_1528(const uint8_t *Data, size_t Size) {
    janet_init();

    fuzz_scan_number_base(Data, Size);
    fuzz_scan_uint64(Data, Size);
    fuzz_scan_numeric(Data, Size);

    janet_deinit(); // Properly deinitialize to prevent memory leaks

    return 0;
}