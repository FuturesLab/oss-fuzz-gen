// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzerror at gzlib.c:513:22 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
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

static void test_gzerror(gzFile file) {
    int errnum;
    const char *error_msg = gzerror(file, &errnum);
    (void)error_msg; // Suppress unused variable warning
}

static void test_gzputc(gzFile file, int c) {
    gzputc(file, c);
}

static void test_gzputs(gzFile file, const char *s) {
    gzputs(file, s);
}

static void test_gzgetc(gzFile file) {
    gzgetc(file);
}

static void test_gzprintf(gzFile file, const char *format, const char *data) {
    gzprintf(file, format, data);
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gz_file = gzopen("./dummy_file", "wb");
    if (!gz_file) return 0;

    // Test gzputc with first byte of data
    test_gzputc(gz_file, Data[0]);

    // Test gzputs with the entire data
    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) {
        gzclose(gz_file);
        return 0;
    }
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';
    test_gzputs(gz_file, buffer);

    // Test gzprintf
    test_gzprintf(gz_file, "%s", buffer);

    // Close and reopen the file for reading
    gzclose(gz_file);
    gz_file = gzopen("./dummy_file", "rb");
    if (!gz_file) {
        free(buffer);
        return 0;
    }

    // Test gzgetc
    test_gzgetc(gz_file);

    // Test gzerror
    test_gzerror(gz_file);

    // Cleanup
    gzclose(gz_file);
    free(buffer);

    return 0;
}