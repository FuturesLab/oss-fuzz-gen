#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static FILE *create_dummy_file() {
    FILE *f = fopen("./dummy_file", "w+");
    if (f) {
        fprintf(f, "dummy data");
        fflush(f);
        rewind(f);
    }
    return f;
}

static void initialize_janet() {
    static int janet_initialized = 0;
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_1371(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    initialize_janet();

    FILE *file = create_dummy_file();
    if (!file) return 0;

    int32_t flags = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetFile *janetFile = janet_makejfile(file, flags);
    if (janetFile) {
        Janet wrappedJanetFile = janet_wrap_abstract(janetFile);

        int32_t unwrapFlags;
        FILE *unwrappedFile = janet_unwrapfile(wrappedJanetFile, &unwrapFlags);

        Janet janetCreatedFile = janet_makefile(unwrappedFile, unwrapFlags);

        JanetFile *retrievedJanetFile = janet_getjfile(&janetCreatedFile, 0);
        if (retrievedJanetFile) {
            int closeResult = janet_file_close(retrievedJanetFile);
        }

        int32_t getFlags;
        FILE *getFile = janet_getfile(&janetCreatedFile, 0, &getFlags);
    } else {
        fclose(file);
    }

    return 0;
}