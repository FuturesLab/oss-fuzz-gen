#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a buffer size
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Open a temporary file to create a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Create a gzFile from the temporary file
    gzFile gzfile = gzdopen(fileno(tempFile), "wb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Extract an unsigned int from the data for buffer size
    unsigned int bufferSize = *((unsigned int*)data);

    // Call the function-under-test
    gzbuffer(gzfile, bufferSize);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}