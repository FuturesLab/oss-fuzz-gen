// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzsetparams at gzwrite.c:630:13 in zlib.h
// gzwrite at gzwrite.c:255:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose_w at gzwrite.c:667:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void fuzz_gzsetparams(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    int level = Data[0] % 10; // Compression level 0-9
    int strategy = Data[1] % 5; // Strategy 0-4
    gzsetparams(file, level, strategy);
}

static void fuzz_gzwrite(gzFile file, const uint8_t *Data, size_t Size) {
    gzwrite(file, Data, Size);
}

static void fuzz_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    gzputc(file, Data[0]);
}

static void fuzz_gzprintf(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    gzprintf(file, "%.*s", (int)Size, Data);
}

static void fuzz_gzerror(gzFile file) {
    int errnum;
    gzerror(file, &errnum);
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    gzFile gzfile = gzopen("./dummy_file", "wb");
    if (!gzfile) return 0;

    fuzz_gzsetparams(gzfile, Data, Size);
    fuzz_gzwrite(gzfile, Data, Size);
    fuzz_gzputc(gzfile, Data, Size);
    fuzz_gzprintf(gzfile, Data, Size);
    fuzz_gzerror(gzfile);

    gzclose_w(gzfile);
    return 0;
}