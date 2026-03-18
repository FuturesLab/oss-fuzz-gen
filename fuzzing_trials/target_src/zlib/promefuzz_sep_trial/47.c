// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzputs at gzwrite.c:350:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzgets at gzread.c:562:16 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// zError at zutil.c:139:22 in zlib.h
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
    if (buffer == NULL) {
        return;
    }
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0'; // Ensure null-termination
    gzputs(file, buffer);
    free(buffer);
}

static void fuzz_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        gzputc(file, Data[0]);
    }
}

static void fuzz_gzgets(gzFile file, size_t Size) {
    char *buffer = (char *)malloc(Size + 1);
    if (buffer == NULL) {
        return;
    }
    gzgets(file, buffer, Size + 1);
    free(buffer);
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    gzFile file = gzopen("./dummy_file", "wb+");
    if (file == NULL) {
        return 0;
    }

    // Fuzz gzputs
    fuzz_gzputs(file, Data, Size);

    // Fuzz gzputc
    fuzz_gzputc(file, Data, Size);

    // Close and reopen the file for reading
    gzclose(file);
    file = gzopen("./dummy_file", "rb");
    if (file == NULL) {
        return 0;
    }

    // Fuzz gzgets
    fuzz_gzgets(file, Size);

    // Fuzz gzgetc
    if (Size > 0) {
        gzgetc(file);
    }

    // Fuzz gzerror
    int errnum;
    gzerror(file, &errnum);

    // Fuzz zError
    zError(errnum);

    gzclose(file);
    return 0;
}