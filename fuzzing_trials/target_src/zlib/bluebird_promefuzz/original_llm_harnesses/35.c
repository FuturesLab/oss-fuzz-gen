// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzungetc at gzread.c:501:13 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzbuffer at gzlib.c:322:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzclose_r at gzread.c:641:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static void fuzz_gzungetc(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        gzungetc(Data[0], file);
    }
}

static void fuzz_gzclearerr(gzFile file) {
    gzclearerr(file);
}

static void fuzz_gzgetc(gzFile file) {
    gzgetc(file);
}

static void fuzz_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        gzputc(file, Data[0]);
    }
}

static void fuzz_gzbuffer(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(unsigned)) {
        unsigned buffer_size = *((unsigned *)Data);
        gzbuffer(file, buffer_size);
    }
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    rewind(dummy_file);

    gzFile gz_file = gzdopen(fileno(dummy_file), "wb+");
    if (!gz_file) {
        fclose(dummy_file);
        return 0;
    }

    fuzz_gzungetc(gz_file, Data, Size);
    fuzz_gzclearerr(gz_file);
    fuzz_gzgetc(gz_file);
    fuzz_gzputc(gz_file, Data, Size);
    fuzz_gzbuffer(gz_file, Data, Size);

    gzclose_r(gz_file);
    fclose(dummy_file);

    return 0;
}