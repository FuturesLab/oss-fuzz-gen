// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
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
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Ensure data for string operations is null-terminated
    char *data_copy = (char *)malloc(Size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, Data, Size);
    data_copy[Size] = '\0';

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Open the file with gzopen
    gzFile file = gzopen("./dummy_file", "wb");
    if (file == NULL) {
        free(data_copy);
        return 0;
    }

    // Call gzputc
    gzputc(file, data_copy[0]);

    // Call gzputs
    gzputs(file, data_copy);

    // Call gzerror
    int errnum;
    gzerror(file, &errnum);

    // Call gzprintf
    gzprintf(file, "Formatted output: %s\n", data_copy);

    // Call gzerror again
    gzerror(file, &errnum);

    // Call gzseek
    gzseek(file, 0, SEEK_SET);

    // Close the file
    gzclose(file);

    // Cleanup
    free(data_copy);

    return 0;
}