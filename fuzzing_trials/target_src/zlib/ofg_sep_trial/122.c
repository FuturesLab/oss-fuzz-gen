#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure there's at least one byte to unget
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to simulate a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Use the first byte of data to call gzungetc
    int char_to_unget = (int)data[0];
    gzungetc(char_to_unget, gzfile);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}