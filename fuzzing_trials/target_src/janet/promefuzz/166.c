// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_string at string.c:49:16 in janet.h
// janet_string_equalconst at string.c:71:5 in janet.h
// janet_cstrcmp at janet.c:34043:5 in janet.h
// janet_string_equal at string.c:82:5 in janet.h
// janet_getstring at janet.c:4516:1 in janet.h
// janet_string_compare at string.c:60:5 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "janet.h"

static JanetString create_janet_string(const uint8_t *data, int32_t len) {
    return janet_string(data, len);
}

static void fuzz_janet_string_equalconst(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    JanetString lhs = create_janet_string(Data, Size - 4);
    const uint8_t *rhs = Data;
    int32_t rlen = (int32_t)Size - 4;
    int32_t rhash = *(int32_t *)(Data + Size - 4);
    int result = janet_string_equalconst(lhs, rhs, rlen, rhash);
}

static void fuzz_janet_cstrcmp(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    JanetString str = create_janet_string(Data, Size - 1);
    char other[Size];
    memcpy(other, Data, Size - 1);
    other[Size - 1] = '\0';
    int result = janet_cstrcmp(str, other);
}

static void fuzz_janet_string_equal(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t half_size = Size / 2;
    JanetString lhs = create_janet_string(Data, half_size);
    JanetString rhs = create_janet_string(Data + half_size, Size - half_size);
    int result = janet_string_equal(lhs, rhs);
}

static void fuzz_janet_getstring(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;

    // Create a Janet array with a single string element
    Janet argv[1];
    argv[0] = janet_wrap_string(create_janet_string(Data, Size - sizeof(Janet) - sizeof(int32_t)));

    int32_t n = *(int32_t *)(Data + (Size - sizeof(int32_t)));
    if (n >= 0 && n < 1) { // Ensure index is within bounds
        JanetString result = janet_getstring(argv, n);
    }
}

static void fuzz_janet_string_compare(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t half_size = Size / 2;
    JanetString lhs = create_janet_string(Data, half_size);
    JanetString rhs = create_janet_string(Data + half_size, Size - half_size);
    int result = janet_string_compare(lhs, rhs);
}

int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size) {
    // Initialize Janet VM before using any Janet functions
    janet_init();
    
    fuzz_janet_string_equalconst(Data, Size);
    fuzz_janet_cstrcmp(Data, Size);
    fuzz_janet_string_equal(Data, Size);
    fuzz_janet_getstring(Data, Size);
    fuzz_janet_string_compare(Data, Size);
    
    // Deinitialize Janet VM after fuzzing
    janet_deinit();
    
    return 0;
}