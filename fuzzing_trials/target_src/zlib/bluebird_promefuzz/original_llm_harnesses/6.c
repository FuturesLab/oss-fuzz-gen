// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Write the input data to a dummy file
    write_dummy_file(Data, Size);

    // Open the file with gzopen
    gzFile file = gzopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }

    // Use gzputc to write a character
    int ret = gzputc(file, Data[0]);
    if (ret == -1) {
        int errnum;
        gzerror(file, &errnum);
    }

    // Prepare a null-terminated string for gzputs
    char *str = (char *)malloc(Size + 1);
    if (!str) {
        gzclose(file);
        return 0;
    }
    memcpy(str, Data, Size);
    str[Size] = '\0';

    // Use gzputs to write a string
    ret = gzputs(file, str);
    if (ret == -1) {
        int errnum;
        gzerror(file, &errnum);
    }

    // Use gzprintf to write formatted data
    ret = gzprintf(file, "Formatted number: %d", Data[0]);
    if (ret < 0) {
        int errnum;
        gzerror(file, &errnum);
    }

    // Use gzseek to change position
    z_off_t offset = gzseek(file, 0, SEEK_SET);
    if (offset == -1) {
        int errnum;
        gzerror(file, &errnum);
    }

    // Clean up
    free(str);
    gzclose(file);

    return 0;
}