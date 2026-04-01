#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data to
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);

    // Rewind the file to the beginning for reading
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    int result = gzgetc(gzfile);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}