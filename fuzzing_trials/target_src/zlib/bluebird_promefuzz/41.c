#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "zlib.h"

static gzFile create_gzfile(const char *filename) {
    return gzopen(filename, "wb");
}

static void write_dummy_file(const char *filename, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static void fuzz_gzprintf(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }
    // Ensure null-termination of format string
    char *format = (char *)malloc(Size + 1);
    if (!format) {
        return;
    }
    memcpy(format, Data, Size);
    format[Size] = '\0';
    gzprintf(file, "%s", format);
    free(format);
}

static void fuzz_gzsetparams(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    int level = Data[0] % 10; // Compression level 0-9
    int strategy = Data[1] % 4; // Strategy 0-3
    gzsetparams(file, level, strategy);
}

static void fuzz_gzwrite(gzFile file, const uint8_t *Data, size_t Size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gzwrite
    gzwrite(file, Data, Z_PARTIAL_FLUSH);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static void fuzz_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }
    gzputc(file, Data[0]);
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    const char *filename = "./dummy_file.gz";
    gzFile file = create_gzfile(filename);
    if (!file) {
        return 0;
    }

    write_dummy_file(filename, Data, Size);

    // Since fuzz_gzvprintf requires a va_list, it is omitted from this fuzzing loop.
    fuzz_gzprintf(file, Data, Size);
    fuzz_gzsetparams(file, Data, Size);
    fuzz_gzwrite(file, Data, Size);
    fuzz_gzputc(file, Data, Size);

    gzclose_w(file);
    return 0;
}