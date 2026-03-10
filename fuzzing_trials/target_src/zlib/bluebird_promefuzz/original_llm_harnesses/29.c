// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzvprintf at gzwrite.c:403:15 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdarg.h>

static gzFile openGzFile() {
    return gzopen("./dummy_file", "w");
}

static void closeGzFile(gzFile file) {
    if (file != NULL) {
        gzclose(file);
    }
}

static void testGzvprintf(gzFile file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    gzvprintf(file, format, args);
    va_end(args);
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated string for gzputs
    char *nullTerminatedString = (char *)malloc(Size + 1);
    if (nullTerminatedString == NULL) return 0;
    memcpy(nullTerminatedString, Data, Size);
    nullTerminatedString[Size] = '\0';

    gzFile file = openGzFile();
    if (file == NULL) {
        free(nullTerminatedString);
        return 0;
    }

    // Test gzputs
    gzputs(file, nullTerminatedString);

    // Test gzputc
    gzputc(file, Data[0]);

    // Test gzprintf
    gzprintf(file, "%s", nullTerminatedString);

    // Test gzvprintf
    testGzvprintf(file, "%s", nullTerminatedString);

    // Test gzerror
    int errnum;
    gzerror(file, &errnum);

    closeGzFile(file);
    free(nullTerminatedString);

    return 0;
}