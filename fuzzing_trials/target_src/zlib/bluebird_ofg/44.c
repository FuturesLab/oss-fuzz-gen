#include <stdint.h>
#include <stdio.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
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
    gzFile gzTempFile = gzdopen(fileno(tempFile), "wb");
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
    file = gzdopen(fileno(tempFile), "rb");
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gzseek to crc32_combine_gen

    uLong ret_crc32_combine_gen_dyxfj = crc32_combine_gen(result);

    // End mutation: Producer.APPEND_MUTATOR

    gzclose(file);
    fclose(tempFile);

    // Return a non-zero value if gzseek fails to increase code coverage
    return (result == -1) ? 1 : 0;
}