// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_getendrange at janet.c:4711:9 in janet.h
// janet_optnat at janet.c:4850:9 in janet.h
// janet_getnat at janet.c:4596:9 in janet.h
// janet_optinteger at janet.c:4856:9 in janet.h
// janet_getinteger at janet.c:4630:9 in janet.h
// janet_getindex at value.c:576:7 in janet.h
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

static Janet create_random_janet(const uint8_t *Data, size_t Size, size_t *offset) {
    Janet janet;
    if (*offset + sizeof(uint64_t) <= Size) {
        janet.u64 = *(uint64_t *)(Data + *offset);
        *offset += sizeof(uint64_t);
    } else {
        janet.u64 = 0;
    }
    return janet;
}

int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 4) return 0; // Ensure there's enough data for arguments

    // Initialize Janet VM
    janet_init();

    size_t offset = 0;
    int32_t argc = *(int32_t *)(Data + offset);
    offset += sizeof(int32_t);
    int32_t n = *(int32_t *)(Data + offset);
    offset += sizeof(int32_t);
    int32_t length = *(int32_t *)(Data + offset);
    offset += sizeof(int32_t);
    int32_t dflt = *(int32_t *)(Data + offset);
    offset += sizeof(int32_t);

    Janet *argv = malloc(argc * sizeof(Janet));
    for (int32_t i = 0; i < argc; i++) {
        argv[i] = create_random_janet(Data, Size, &offset);
    }

    if (n >= 0 && n < argc) {
        janet_getendrange(argv, argc, n, length);
        janet_optnat(argv, argc, n, dflt);
        janet_getnat(argv, n);
        janet_optinteger(argv, argc, n, dflt);
        janet_getinteger(argv, n);
    }

    if (Size - offset >= sizeof(Janet)) {
        Janet ds = create_random_janet(Data, Size, &offset);
        janet_getindex(ds, n);
    }

    free(argv);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}