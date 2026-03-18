#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Define the LLVMFuzzerTestOneInput function without extern "C"
int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to unget
    if (size < 1) {
        return 0;
    }

    // Initialize a gzFile object using a memory buffer
    gzFile gz_file = gzdopen(fileno(tmpfile()), "wb+");
    if (gz_file == NULL) {
        return 0;
    }

    // Write the data to the gzFile
    if (gzwrite(gz_file, data, size) != (int)size) {
        gzclose(gz_file);
        return 0;
    }

    // Rewind the gzFile to the beginning
    if (gzseek(gz_file, 0, SEEK_SET) < 0) {
        gzclose(gz_file);
        return 0;
    }

    // Call gzungetc with the first byte of data
    int byte_to_unget = data[0];
    gzungetc(byte_to_unget, gz_file);

    // Clean up
    gzclose(gz_file);

    return 0;
}