// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_optstruct at janet.c:4528:1 in janet.h
// janet_struct_begin at janet.c:32494:10 in janet.h
// janet_struct_find at janet.c:32513:16 in janet.h
// janet_getstruct at janet.c:4515:1 in janet.h
// janet_struct_end at janet.c:32603:16 in janet.h
// janet_struct_get_ex at janet.c:32643:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

static void init_janet_vm() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_optstruct(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 3) return;

    const Janet *argv = (const Janet *)Data;
    int32_t argc = (int32_t)(Size / sizeof(Janet));
    int32_t n = (int32_t)(argv[0].i64 % argc);
    JanetStruct dflt = (JanetStruct)(argv + 1);

    janet_optstruct(argv, argc, n, dflt);
}

static void fuzz_janet_struct_begin(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;

    int32_t count = *(int32_t *)Data;

    janet_struct_begin(count);
}

static void fuzz_janet_struct_find(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;

    JanetStruct st = (JanetStruct)Data;
    Janet key = *(Janet *)(Data + sizeof(Janet));

    janet_struct_find(st, key);
}

static void fuzz_janet_getstruct(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return;

    const Janet *argv = (const Janet *)Data;
    int32_t n = (int32_t)(argv[0].i64 % (Size / sizeof(Janet)));

    janet_getstruct(argv, n);
}

static void fuzz_janet_struct_end(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetKV)) return;

    JanetKV *st = (JanetKV *)Data;

    janet_struct_end(st);
}

static void fuzz_janet_struct_get_ex(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 3) return;

    JanetStruct st = (JanetStruct)Data;
    Janet key = *(Janet *)(Data + sizeof(Janet));
    JanetStruct which;

    janet_struct_get_ex(st, key, &which);
}

int LLVMFuzzerTestOneInput_785(const uint8_t *Data, size_t Size) {
    init_janet_vm();
    fuzz_janet_optstruct(Data, Size);
    fuzz_janet_struct_begin(Data, Size);
    fuzz_janet_struct_find(Data, Size);
    fuzz_janet_getstruct(Data, Size);
    fuzz_janet_struct_end(Data, Size);
    fuzz_janet_struct_get_ex(Data, Size);
    return 0;
}