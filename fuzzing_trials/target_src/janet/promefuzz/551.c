// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_string_begin at string.c:34:10 in janet.h
// janet_string_end at string.c:43:16 in janet.h
// janet_symbol at janet.c:32957:16 in janet.h
// janet_to_string at janet.c:28692:16 in janet.h
// janet_getstring at janet.c:4516:1 in janet.h
// janet_string at string.c:49:16 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static int janet_initialized = 0;

static void initialize_janet() {
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

static void fuzz_janet_string_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t length = *(int32_t *)Data;
    if (length < 0) return; // Ensure length is non-negative
    uint8_t *result = janet_string_begin(length);
    if (result) {
        // Properly finalize the string creation
        janet_string_end(result);
    }
}

static void fuzz_janet_symbol(const uint8_t *Data, size_t Size) {
    if (Size == 0) return; // Ensure Data is not empty
    JanetSymbol sym = janet_symbol(Data, (int32_t)Size);
    (void)sym; // Use sym or perform checks if necessary
}

static void fuzz_janet_to_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;
    Janet x;
    memcpy(&x, Data, sizeof(Janet));
    JanetString str = janet_to_string(x);
    (void)str; // Use str or perform checks if necessary
}

static void fuzz_janet_getstring(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;
    const Janet *argv = (const Janet *)Data;
    int32_t n = *(int32_t *)(Data + sizeof(Janet));
    JanetString str = janet_getstring(argv, n);
    (void)str; // Use str or perform checks if necessary
}

static void fuzz_janet_string(const uint8_t *Data, size_t Size) {
    JanetString str = janet_string(Data, (int32_t)Size);
    (void)str; // Use str or perform checks if necessary
}

int LLVMFuzzerTestOneInput_551(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_string_begin(Data, Size);
    fuzz_janet_symbol(Data, Size);
    fuzz_janet_to_string(Data, Size);
    fuzz_janet_getstring(Data, Size);
    fuzz_janet_string(Data, Size);
    return 0;
}