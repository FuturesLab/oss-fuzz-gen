#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <assert.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Create a temporary file to use with gzFile
    const char *filename = "/tmp/fuzz_gzfile.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    z_off_t offset = gztell(gzfile);
    (void)offset;  // Suppress unused variable warning

    // Close the gzFile
    gzclose(gzfile);

    return 0;
}