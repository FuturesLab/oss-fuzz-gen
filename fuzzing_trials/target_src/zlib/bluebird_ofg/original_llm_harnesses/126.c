#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

// Fuzzing harness for gzclearerr function
int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Create a temporary file to use with gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        remove(filename);
        return 0;
    }

    // Call the function-under-test
    gzclearerr(gzfile);

    // Clean up
    gzclose(gzfile);
    remove(filename);

    return 0;
}