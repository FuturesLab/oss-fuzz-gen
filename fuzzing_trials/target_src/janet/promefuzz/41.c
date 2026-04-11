// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_getargindex at janet.c:4718:9 in janet.h
// janet_optcbytes at janet.c:4589:13 in janet.h
// janet_optcstring at janet.c:4542:13 in janet.h
// janet_getcstring at janet.c:4553:13 in janet.h
// janet_getcbytes at janet.c:4560:13 in janet.h
// janet_getfile at janet.c:18322:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

#define MAX_ARGV_LENGTH 10
#define DUMMY_STRING "default"
#define DUMMY_FILE "./dummy_file"

static void prepare_dummy_file() {
    FILE *file = fopen(DUMMY_FILE, "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * MAX_ARGV_LENGTH) {
        return 0;
    }

    Janet argv[MAX_ARGV_LENGTH];
    memcpy(argv, Data, sizeof(Janet) * MAX_ARGV_LENGTH);

    int32_t flags = 0;
    prepare_dummy_file();

    // Fuzz janet_getargindex
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 2)) {
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH];
        int32_t length = ((int32_t *)Data)[MAX_ARGV_LENGTH + 1];
        janet_getargindex(argv, n, length, "index");
    }

    // Fuzz janet_optcbytes
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 3)) {
        int32_t argc = ((int32_t *)Data)[MAX_ARGV_LENGTH + 2];
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH + 3];
        janet_optcbytes(argv, argc, n, DUMMY_STRING);
    }

    // Fuzz janet_optcstring
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 4)) {
        int32_t argc = ((int32_t *)Data)[MAX_ARGV_LENGTH + 4];
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH + 5];
        janet_optcstring(argv, argc, n, DUMMY_STRING);
    }

    // Fuzz janet_getcstring
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 5)) {
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH + 6];
        janet_getcstring(argv, n);
    }

    // Fuzz janet_getcbytes
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 6)) {
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH + 7];
        janet_getcbytes(argv, n);
    }

    // Fuzz janet_getfile
    if (Size >= sizeof(Janet) * (MAX_ARGV_LENGTH + 7)) {
        int32_t n = ((int32_t *)Data)[MAX_ARGV_LENGTH + 8];
        FILE *file = janet_getfile(argv, n, &flags);
        if (file) {
            fclose(file);
        }
    }

    return 0;
}