#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    gzFile file;
    int character;
    char filename[] = "/tmp/fuzz_gzputc.gz";

    // Open a file for writing in gzip mode
    file = gzopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Ensure that size is greater than 0 to read at least one byte
    if (size > 0) {
        // Use the first byte of data as the character to write
        character = (int)data[0];
    } else {
        // Default character if size is 0
        character = 'A';
    }

    // Call the function-under-test
    gzputc(file, character);

    // Close the file
    gzclose(file);

    return 0;
}