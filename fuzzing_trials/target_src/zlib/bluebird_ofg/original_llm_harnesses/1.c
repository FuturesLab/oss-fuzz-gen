#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    gzFile file;
    unsigned int len;
    void *buffer;

    // Ensure the size is non-zero to avoid division by zero
    if (size == 0) {
        return 0;
    }

    // Prepare a temporary file to write the gzipped data
    file = gzopen("temp.gz", "wb");
    if (file == NULL) {
        return 0;
    }

    // Use the data as the buffer to write
    buffer = (void*)data;
    len = (unsigned int)size;

    // Call the function under test
    gzwrite(file, buffer, len);

    // Close the file
    gzclose(file);

    // Remove the temporary file
    remove("temp.gz");

    return 0;
}