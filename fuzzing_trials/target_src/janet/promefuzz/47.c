// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_scan_number_base at strtod.c:252:5 in janet.h
// janet_scan_uint64 at strtod.c:486:5 in janet.h
// janet_scan_numeric at strtod.c:500:5 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
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
    if (size < 1) return;

    double out;
    int32_t base = (data[0] % 36) + 1; // base between 1 and 36
    janet_scan_number_base(data + 1, size - 1, base, &out);
}

static void fuzz_scan_uint64(const uint8_t *data, size_t size) {
    if (size < 1) return;

    uint64_t out;
    janet_scan_uint64(data, (int32_t)size, &out);
}

static void fuzz_scan_numeric(const uint8_t *data, size_t size) {
    if (size < 1) return;

    Janet out;
    janet_scan_numeric(data, (int32_t)size, &out);
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    janet_init();

    fuzz_scan_number_base(Data, Size);
    fuzz_scan_uint64(Data, Size);
    fuzz_scan_numeric(Data, Size);

    janet_deinit(); // Properly deinitialize to prevent memory leaks

    return 0;
}