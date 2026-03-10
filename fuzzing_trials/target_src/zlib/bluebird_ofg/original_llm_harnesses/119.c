#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write data to the temporary file
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
    int result = gzdirect(gzfile);

    // Close the gzFile and the temporary file
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}