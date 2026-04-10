// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_equals at value.c:249:5 in janet.h
// janet_checkint at janet.c:34521:5 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_tuple_begin at tuple.c:34:8 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_compare at value.c:371:5 in janet.h
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_equals(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;
    Janet x = *(Janet *)(Data);
    Janet y = *(Janet *)(Data + sizeof(Janet));
    janet_equals(x, y);
}

static void fuzz_janet_checkint(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x = *(Janet *)(Data);
    janet_checkint(x);
}

static void fuzz_janet_tuple_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t length = *(int32_t *)(Data);

    // Ensure the length is non-negative to avoid undefined behavior
    if (length < 0) return;

    janet_init();
    Janet *tuple = janet_tuple_begin(length);
    (void)tuple; // Suppress unused variable warning
    janet_deinit();
}

static void fuzz_janet_compare(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;
    Janet x = *(Janet *)(Data);
    Janet y = *(Janet *)(Data + sizeof(Janet));
    janet_compare(x, y);
}

static void fuzz_janet_wrap_integer(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t x = *(int32_t *)(Data);
    janet_wrap_integer(x);
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    fuzz_janet_equals(Data, Size);
    fuzz_janet_checkint(Data, Size);
    fuzz_janet_tuple_begin(Data, Size);
    fuzz_janet_compare(Data, Size);
    fuzz_janet_wrap_integer(Data, Size);
    return 0;
}