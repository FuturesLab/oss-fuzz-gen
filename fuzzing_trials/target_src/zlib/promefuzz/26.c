// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzputs at gzwrite.c:350:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdarg.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static void test_gzputs(gzFile file, const uint8_t *Data, size_t Size) {
    char *buffer = malloc(Size + 1);
    if (buffer) {
        memcpy(buffer, Data, Size);
        buffer[Size] = '\0';
        gzputs(file, buffer);
        free(buffer);
    }
}

static void test_gzprintf(gzFile file, const uint8_t *Data, size_t Size) {
    char *format = malloc(Size + 1);
    if (format) {
        memcpy(format, Data, Size);
        format[Size] = '\0';
        gzprintf(file, format);
        free(format);
    }
}

static void test_gzputc(gzFile file, const uint8_t *Data, size_t Size) {
    for (size_t i = 0; i < Size; i++) {
        gzputc(file, Data[i]);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    write_dummy_file(Data, Size);

    gzFile file = gzopen("./dummy_file", "wb");
    if (file == NULL) {
        return 0;
    }

    test_gzputs(file, Data, Size);
    test_gzprintf(file, Data, Size);
    test_gzputc(file, Data, Size);

    int errnum;
    gzerror(file, &errnum);

    gzclose(file);
    return 0;
}