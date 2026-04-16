// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_optsize at janet.c:4868:8 in janet.h
// janet_unmarshal at marsh.c:1635:7 in janet.h
// janet_getsize at janet.c:4687:8 in janet.h
// janet_optsymbol at janet.c:4531:1 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static Janet make_janet_value(uint64_t u64) {
    Janet value;
    value.u64 = u64;
    return value;
}

int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize the Janet environment
    janet_init();

    // Prepare data for janet_optsize
    Janet argv_optsize[3];
    for (int i = 0; i < 3; i++) {
        argv_optsize[i] = make_janet_value(i < Size ? Data[i] : 0);
    }
    size_t default_size = 10;
    janet_optsize(argv_optsize, 3, 1, default_size);

    // Prepare data for janet_unmarshal
    const uint8_t *next = NULL;
    JanetTable reg = {0};
    if (Size > 0) {
        janet_unmarshal(Data, Size, 0, &reg, &next);
    }

    // Prepare data for janet_getsize
    Janet argv_getsize[2];
    for (int i = 0; i < 2; i++) {
        argv_getsize[i] = make_janet_value(i < Size ? Data[i] : 0);
    }
    if (Size > 0) {
        janet_getsize(argv_getsize, 1);
    }

    // Prepare data for janet_optsymbol
    Janet argv_optsymbol[3];
    for (int i = 0; i < 3; i++) {
        argv_optsymbol[i] = make_janet_value(i < Size ? Data[i] : 0);
    }
    JanetSymbol default_symbol = (JanetSymbol)"default";
    janet_optsymbol(argv_optsymbol, 3, 1, default_symbol);

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}