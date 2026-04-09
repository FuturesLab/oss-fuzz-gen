// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_gethalfrange at janet.c:4695:9 in janet.h
// janet_getargindex at janet.c:4718:9 in janet.h
// janet_optcbytes at janet.c:4589:13 in janet.h
// janet_getstartrange at janet.c:4704:9 in janet.h
// janet_getcbytes at janet.c:4560:13 in janet.h
// janet_getnat at janet.c:4596:9 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static Janet *generate_random_janet_array(size_t count) {
    Janet *array = (Janet *)malloc(count * sizeof(Janet));
    for (size_t i = 0; i < count; i++) {
        switch (rand() % 4) {
            case 0:
                array[i].u64 = rand();
                break;
            case 1:
                array[i].i64 = rand() - (RAND_MAX / 2);
                break;
            case 2:
                array[i].number = (double)rand() / RAND_MAX;
                break;
            case 3:
                array[i].pointer = NULL;
                break;
        }
    }
    return array;
}

int LLVMFuzzerTestOneInput_572(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t) * 3 + 1) return 0;

    int32_t n = *((int32_t *)Data);
    int32_t length = *((int32_t *)(Data + sizeof(int32_t)));
    int32_t argc = *((int32_t *)(Data + 2 * sizeof(int32_t)));
    const char *which = (const char *)(Data + 3 * sizeof(int32_t));

    if (argc <= 0) return 0;

    Janet *argv = generate_random_janet_array(argc);

    // Fuzz janet_gethalfrange
    if (n >= 0 && n < length) {
        janet_gethalfrange(argv, n, length, which);
    }

    // Fuzz janet_getargindex
    if (n >= 0 && n < length) {
        janet_getargindex(argv, n, length, which);
    }

    // Fuzz janet_optcbytes
    const char *dflt = "default";
    janet_optcbytes(argv, argc, n, dflt);

    // Fuzz janet_getstartrange
    if (n < argc && n >= 0 && length > 0) {
        janet_getstartrange(argv, argc, n, length);
    }

    // Fuzz janet_getcbytes
    if (n >= 0 && n < argc) {
        janet_getcbytes(argv, n);
    }

    // Fuzz janet_getnat
    if (n >= 0 && n < argc) {
        janet_getnat(argv, n);
    }

    free(argv);
    return 0;
}