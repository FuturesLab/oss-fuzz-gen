#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>  // Include this header to define off_t

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        return 0;
    }
    fclose(file);

    // Open the file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    off_t offset = gztell(gzfile);

    // Close the gzFile
    gzclose(gzfile);

    // Remove the temporary file
    remove(filename);

    return 0;
}