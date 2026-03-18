#include <stdint.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

// Define the function without extern "C"
int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    gzFile file;
    off_t offset;
    int whence;
    char filename[] = "/tmp/fuzz_gzseek.gz";

    // Ensure the size is sufficient to extract meaningful values
    if (size < sizeof(off_t) + sizeof(int)) {
        return 0;
    }

    // Create a temporary file to be used with gzseek
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return 0;
    }
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Extract offset and whence from the input data
    offset = *(off_t *)data;
    whence = *(int *)(data + sizeof(off_t));

    // Call gzseek with the extracted values
    (void)gzseek(file, offset, whence);

    // Close the gzFile
    gzclose(file);

    // Remove the temporary file
    remove(filename);

    return 0;
}