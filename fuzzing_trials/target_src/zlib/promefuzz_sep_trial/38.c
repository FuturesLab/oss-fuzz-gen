// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzvprintf at gzwrite.c:403:15 in zlib.h
// gzsetparams at gzwrite.c:630:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzclose_w at gzwrite.c:667:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdarg.h>

static gzFile initialize_gzfile() {
    return gzopen("./dummy_file", "wb");
}

static void fuzz_gzvprintf(gzFile file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    gzvprintf(file, format, args);
    va_end(args);
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize gzFile
    gzFile file = initialize_gzfile();
    if (file == NULL) return 0;

    // Fuzz gzsetparams
    int level = Data[0] % 10;  // Compression level between 0 and 9
    int strategy = Data[0] % 5;  // Strategy between 0 and 4
    gzsetparams(file, level, strategy);

    // Fuzz gzputc
    for (size_t i = 0; i < Size; ++i) {
        gzputc(file, Data[i]);
    }

    // Fuzz gzprintf
    gzprintf(file, "Fuzzing gzprintf with size: %zu\n", Size);

    // Fuzz gzvprintf
    fuzz_gzvprintf(file, "Fuzzing gzvprintf with size: %zu\n", Size);

    // Fuzz gzerror
    int errnum;
    const char *error_msg = gzerror(file, &errnum);

    // Finalize by closing the file
    gzclose_w(file);

    return 0;
}