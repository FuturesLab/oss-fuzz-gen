#include <stdint.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = gzclose(gzfile);

    // Remove the temporary file
    remove(filename);

    return result;
}