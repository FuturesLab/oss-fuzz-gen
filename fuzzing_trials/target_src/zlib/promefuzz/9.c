// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzwrite at gzwrite.c:255:13 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    // Open the dummy file with gzopen in write mode
    gzFile gzfile = gzopen("./dummy_file", "wb");
    if (gzfile == NULL) {
        return 0;
    }

    // Attempt to write the data to the gzfile
    gzwrite(gzfile, Data, Size);

    // Fetch and print the last error if any
    int errnum;
    const char *error_message = gzerror(gzfile, &errnum);
    if (errnum != Z_OK) {
        fprintf(stderr, "gzerror: %s\n", error_message);
    }

    // Close the gzfile
    gzclose(gzfile);

    return 0;
}