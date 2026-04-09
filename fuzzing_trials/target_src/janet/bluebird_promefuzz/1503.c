#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static Janet create_janet_number(double num) {
    Janet j;
    j.number = num;
    return j;
}

static Janet create_janet_u64(uint64_t u) {
    Janet j;
    j.u64 = u;
    return j;
}

int LLVMFuzzerTestOneInput_1503(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test janet_checkuint
    {
        Janet j = create_janet_number((double)Data[0]);
        janet_checkuint(j);
    }

    // Test janet_getnumber
    if (Size >= sizeof(Janet)) {
        Janet argv[1];
        memcpy(&argv[0], Data, sizeof(Janet));
        if (argv[0].number == argv[0].number) { // Ensure it's a number
            janet_getnumber(argv, 0);
        }
    }

    // Test janet_checkuint64
    {
        Janet j = create_janet_u64((uint64_t)Data[0]);
        janet_checkuint64(j);
    }

    // Test janet_scan_number_base
    if (Size > 1) {
        double out;
        int32_t base = (int32_t)(Data[0] % 36 + 2); // base between 2 and 36
        janet_scan_number_base(Data + 1, Size - 1, base, &out);
    }

    // Test janet_optnumber
    if (Size >= sizeof(Janet) * 3) {
        Janet argv[3];
        memcpy(argv, Data, sizeof(Janet) * 3);
        if (argv[0].number == argv[0].number) { // Ensure it's a number
            janet_optnumber(argv, 3, 0, 0.0);
        }
    }

    // Test janet_scan_number
    if (Size > 0) {
        double out;
        janet_scan_number(Data, Size, &out);
    }

    return 0;
}