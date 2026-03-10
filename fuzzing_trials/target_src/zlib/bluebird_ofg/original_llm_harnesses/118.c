#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize a buffer with the input data
    char filename[] = "/tmp/fuzz_input.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to a file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = gzdirect(gzfile);

    // Close the gzFile
    gzclose(gzfile);

    return 0;
}