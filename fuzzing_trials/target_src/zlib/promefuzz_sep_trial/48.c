// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzputs at gzwrite.c:350:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzgets at gzread.c:562:16 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void fuzz_gzputs(gzFile file, const uint8_t *Data, size_t Size) {
    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) return;
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0'; // Ensure null-termination

    gzputs(file, buffer);
    free(buffer);
}

static void fuzz_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    for (size_t i = 0; i < Size; ++i) {
        gzputc(file, Data[i]);
    }
}

static void fuzz_gzgets(gzFile file, size_t Size) {
    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) return;

    gzgets(file, buffer, Size);
    free(buffer);
}

static void fuzz_gzerror(gzFile file) {
    int errnum;
    gzerror(file, &errnum);
}

static void fuzz_gzgetc(gzFile file) {
    gzgetc(file);
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *fp = fopen("./dummy_file", "wb+");
    if (!fp) return 0;

    fwrite(Data, 1, Size, fp);
    fclose(fp);

    gzFile gzfile = gzopen("./dummy_file", "wb+");
    if (!gzfile) return 0;

    fuzz_gzputs(gzfile, Data, Size);
    fuzz_gzputc(gzfile, Data, Size);
    gzclose(gzfile);

    gzfile = gzopen("./dummy_file", "rb");
    if (!gzfile) return 0;

    fuzz_gzgets(gzfile, Size);
    fuzz_gzgetc(gzfile);
    fuzz_gzerror(gzfile);

    gzclose(gzfile);

    return 0;
}