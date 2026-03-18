#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen for writing
    gzFile gzfile = gzopen(filename, "wb");
    if (gzfile == NULL) {
        remove(filename);
        return 0;
    }

    // Write some data to the gzfile to simulate usage
    gzwrite(gzfile, data, size > 0 ? size : 1);

    // Call the function-under-test
    int result = gzclose_w(gzfile);

    // Clean up the temporary file
    remove(filename);

    return result;
}