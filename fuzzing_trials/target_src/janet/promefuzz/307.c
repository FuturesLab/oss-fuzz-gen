// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_optstruct at janet.c:4528:1 in janet.h
// janet_struct_put at janet.c:32598:6 in janet.h
// janet_struct_begin at janet.c:32494:10 in janet.h
// janet_struct_find at janet.c:32513:16 in janet.h
// janet_struct_rawget at janet.c:32626:7 in janet.h
// janet_getstruct at janet.c:4515:1 in janet.h
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
#include <string.h>
#include "janet.h"

static Janet create_random_janet(const uint8_t *data, size_t size) {
    Janet janet;
    if (size >= sizeof(uint64_t)) {
        janet.u64 = *((uint64_t *)data);
    } else {
        janet.u64 = 0;
    }
    return janet;
}

static void fuzz_janet_optstruct(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) * 2 + sizeof(int32_t) * 2) return;

    Janet argv[2];
    memcpy(argv, data, sizeof(Janet) * 2);
    int32_t argc = 2;
    int32_t n = *((int32_t *)(data + sizeof(Janet) * 2));
    JanetStruct dflt = (JanetStruct)(data + sizeof(Janet) * 2 + sizeof(int32_t));

    janet_optstruct(argv, argc, n, dflt);
}

static void fuzz_janet_struct_put(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetKV) + sizeof(Janet) * 2) return;

    JanetKV *st = (JanetKV *)malloc(sizeof(JanetKV) * 2);
    if (!st) return;
    memcpy(st, data, sizeof(JanetKV));
    Janet key = create_random_janet(data + sizeof(JanetKV), size - sizeof(JanetKV));
    Janet value = create_random_janet(data + sizeof(JanetKV) + sizeof(Janet), size - sizeof(JanetKV) - sizeof(Janet));

    janet_struct_put(st, key, value);
    free(st);
}

static void fuzz_janet_struct_begin(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) return;

    int32_t count = *((int32_t *)data);
    JanetKV *st = janet_struct_begin(count);
    free(st);
}

static void fuzz_janet_struct_find(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetStruct) + sizeof(Janet)) return;

    JanetStruct st = (JanetStruct)data;
    Janet key = create_random_janet(data + sizeof(JanetStruct), size - sizeof(JanetStruct));

    janet_struct_find(st, key);
}

static void fuzz_janet_struct_rawget(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetStruct) + sizeof(Janet)) return;

    JanetStruct st = (JanetStruct)data;
    Janet key = create_random_janet(data + sizeof(JanetStruct), size - sizeof(JanetStruct));

    janet_struct_rawget(st, key);
}

static void fuzz_janet_getstruct(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) * 2 + sizeof(int32_t)) return;

    Janet argv[2];
    memcpy(argv, data, sizeof(Janet) * 2);
    int32_t n = *((int32_t *)(data + sizeof(Janet) * 2));

    janet_getstruct(argv, n);
}

int LLVMFuzzerTestOneInput_307(const uint8_t *Data, size_t Size) {
    /* Initialize the Janet VM */
    janet_init();

    fuzz_janet_optstruct(Data, Size);
    fuzz_janet_struct_put(Data, Size);
    fuzz_janet_struct_begin(Data, Size);
    fuzz_janet_struct_find(Data, Size);
    fuzz_janet_struct_rawget(Data, Size);
    fuzz_janet_getstruct(Data, Size);

    /* Deinitialize the Janet VM */
    janet_deinit();

    return 0;
}