#include <stdint.h>
#include <stdio.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    gzFile file;
    off_t offset;
    int whence;
    off_t result;

    // Create a temporary file to work with
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Open a gzFile for writing to compress the input data

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of gzdopen
    gzFile gzTempFile = gzdopen(Z_MEM_ERROR, "wb");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (gzTempFile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Write the input data to the gzFile to compress it
    gzwrite(gzTempFile, data, size);
    gzclose(gzTempFile);

    // Rewind the file to the beginning for reading
    rewind(tempFile);

    // Open the temporary file as a gzFile for reading

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of gzdopen
    file = gzdopen(Z_ERRNO, "rb");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (file == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Set offset and whence to some values for testing
    offset = (off_t)(size / 2); // Use half of the size as an offset
    whence = SEEK_SET; // Use SEEK_SET as the whence value

    // Call the function-under-test
    result = gzseek(file, offset, whence);

    // Close the gzFile and the temporary file
    gzclose(file);
    fclose(tempFile);

    // Return a non-zero value if gzseek fails to increase code coverage
    return (result == -1) ? 1 : 0;
}