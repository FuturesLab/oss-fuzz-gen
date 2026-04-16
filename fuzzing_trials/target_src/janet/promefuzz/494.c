// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_makejfile at janet.c:18328:12 in janet.h
// janet_file_close at janet.c:17826:5 in janet.h
// janet_makefile at janet.c:18332:7 in janet.h
// janet_unwrapfile at janet.c:18340:7 in janet.h
// janet_getjfile at janet.c:18318:12 in janet.h
// janet_file_close at janet.c:17826:5 in janet.h
// janet_getfile at janet.c:18322:7 in janet.h
// janet_file_close at janet.c:17826:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static FILE *open_dummy_file() {
    FILE *f = fopen("./dummy_file", "w+");
    if (f) {
        fprintf(f, "dummy content");
        fseek(f, 0, SEEK_SET);
    }
    return f;
}

static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static void fuzz_janet_makejfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    FILE *f = open_dummy_file();
    if (!f) return;
    int32_t flags;
    memcpy(&flags, Data, sizeof(int32_t));
    JanetFile *jfile = janet_makejfile(f, flags);
    if (jfile) {
        janet_file_close(jfile);
    } else {
        fclose(f);
    }
}

static void fuzz_janet_makefile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    FILE *f = open_dummy_file();
    if (!f) return;
    int32_t flags;
    memcpy(&flags, Data, sizeof(int32_t));
    Janet janet_file = janet_makefile(f, flags);
    int32_t out_flags;
    FILE *unwrapped = janet_unwrapfile(janet_file, &out_flags);
    if (unwrapped && unwrapped != f) {
        fclose(unwrapped);
    }
    fclose(f);
}

static void fuzz_janet_getjfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;
    Janet argv[1];
    memcpy(&argv[0], Data, sizeof(Janet));
    int32_t index;
    memcpy(&index, Data + sizeof(Janet), sizeof(int32_t));
    JanetFile *jfile = janet_getjfile(argv, index);
    if (jfile) {
        janet_file_close(jfile);
    }
}

static void fuzz_janet_getfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t)) return;
    Janet argv[1];
    memcpy(&argv[0], Data, sizeof(Janet));
    int32_t index;
    memcpy(&index, Data + sizeof(Janet), sizeof(int32_t));
    int32_t out_flags;
    FILE *file = janet_getfile(argv, index, &out_flags);
    if (file) {
        fclose(file);
    }
}

static void fuzz_janet_file_close(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetFile *)) return;
    JanetFile *jfile;
    memcpy(&jfile, Data, sizeof(JanetFile *));
    // Validate the pointer before using it
    if (jfile && jfile->file != NULL) {
        janet_file_close(jfile);
    }
}

int LLVMFuzzerTestOneInput_494(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_makejfile(Data, Size);
    fuzz_janet_makefile(Data, Size);
    fuzz_janet_getjfile(Data, Size);
    fuzz_janet_getfile(Data, Size);
    fuzz_janet_file_close(Data, Size);
    return 0;
}