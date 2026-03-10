#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    gzFile file;
    const char *filename = "fuzz_output.gz";
    unsigned int len = size > 0 ? size : 1; // Ensure len is not zero

    // Open a gzip file for writing
    file = gzopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gzwrite(file, (const void *)data, len);

    // Close the gzip file
    gzclose(file);

    // Remove the file after writing to avoid clutter
    remove(filename);

    return 0;
}