// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_796(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + 2 * sizeof(int32_t) + sizeof(Janet)) {
        return 0;
    }

    // Prepare dummy file
    prepare_dummy_file(Data, Size);

    // Initialize variables
    double num = *(double *)Data;
    int32_t idx = *(int32_t *)(Data + sizeof(double));
    int32_t base = *(int32_t *)(Data + sizeof(double) + sizeof(int32_t));
    Janet janetValue = *(Janet *)(Data + sizeof(double) + 2 * sizeof(int32_t));
    const uint8_t *str = Data + sizeof(double) + 2 * sizeof(int32_t) + sizeof(Janet);
    int32_t str_len = (int32_t)(Size - (sizeof(double) + 2 * sizeof(int32_t) + sizeof(Janet)));
    double out;
    Janet argv[3] = {janet_nanbox_from_double(num), janetValue, janet_nanbox_from_double(0.0)};
    int32_t argc = 3;

    // Fuzz janet_getnumber
    if (idx >= 0 && idx < argc && argv[idx].u64 == argv[idx].number) {
        double result = janet_getnumber(argv, idx);
    }

    // Fuzz janet_scan_number_base
    if (str_len > 0) {
        int parse_result = janet_scan_number_base(str, str_len, base, &out);
    }

    // Fuzz janet_nanbox_from_double
    Janet janetFromDouble = janet_nanbox_from_double(num);

    // Fuzz janet_wrap_number_safe
    Janet janetWrappedSafe = janet_wrap_number_safe(num);

    // Fuzz janet_optnumber
    if (idx >= 0 && idx < argc) {
        double optnumber = janet_optnumber(argv, argc, idx, num);
    }

    // Fuzz janet_unwrap_number
    if (janetValue.u64 == janetValue.number) {
        double unwrapped = janet_unwrap_number(janetValue);
    }

    return 0;
}