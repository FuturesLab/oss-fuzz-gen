#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    gzFile file;
    int result;
    char filename[] = "/tmp/fuzz_input.gz";

    // Create a temporary file and write the input data to it
    FILE *temp_file = fopen(filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }

    if (fwrite(data, 1, size, temp_file) != size) {
        fclose(temp_file);
        return 0;
    }
    fclose(temp_file);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    result = gzdirect(file);

    // Close the gzFile
    gzclose(file);

    return 0;
}