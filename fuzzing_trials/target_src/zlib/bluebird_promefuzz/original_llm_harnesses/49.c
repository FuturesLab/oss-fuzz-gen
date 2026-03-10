// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzputs at gzwrite.c:350:13 in zlib.h
// gzgets at gzread.c:562:16 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzrewind at gzlib.c:346:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// zlibVersion at zutil.c:27:22 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void fuzz_gzputs(gzFile file, const uint8_t *Data, size_t Size) {
    // Allocate a buffer and ensure null termination
    char *buffer = (char *)malloc(Size + 1);
    if (buffer == NULL) {
        return;
    }
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    // Use gzputs to write the string to the gzFile
    gzputs(file, buffer);

    free(buffer);
}

static void fuzz_gzgets(gzFile file, size_t Size) {
    // Allocate a buffer for reading
    char *buffer = (char *)malloc(Size + 1);
    if (buffer == NULL) {
        return;
    }

    // Use gzgets to read a line from the gzFile
    gzgets(file, buffer, (int)Size);

    free(buffer);
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data for meaningful operations
    if (Size < 1) {
        return 0;
    }

    // Open a gzipped file for writing and reading
    gzFile gzfile = gzopen("./dummy_file", "w+");
    if (gzfile == NULL) {
        return 0;
    }

    // Fuzz gzputs with the given data
    fuzz_gzputs(gzfile, Data, Size);

    // Rewind the file to the beginning for reading
    gzrewind(gzfile);

    // Fuzz gzgets with the given data
    fuzz_gzgets(gzfile, Size);

    // Get a single character with gzgetc
    gzgetc(gzfile);

    // Retrieve the last error message
    int errnum;
    gzerror(gzfile, &errnum);

    // Close the gzFile
    gzclose(gzfile);

    // Check zlib version
    zlibVersion();

    return 0;
}