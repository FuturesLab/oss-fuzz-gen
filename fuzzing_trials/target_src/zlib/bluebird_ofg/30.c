#include <stdint.h>
#include <stddef.h>
#include "zlib.h"
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    gzFile file;
    char filename[] = "/tmp/fuzz_gzfile.gz";

    // Write the input data to a temporary file
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

    // Call the function-under-test
    z_off_t offset = gztell(file);

    // Print the offset for debugging purposes (optional)
    printf("Offset: %lld\n", (long long)offset);

    // Close the gzFile
    gzclose(file);

    // Remove the temporary file
    remove(filename);

    return 0;
}