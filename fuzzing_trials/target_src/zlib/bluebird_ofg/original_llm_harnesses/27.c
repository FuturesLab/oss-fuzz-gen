#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    gzFile file;
    char filename[] = "/tmp/fuzz_input.gz";

    // Write the input data to a temporary file
    FILE *temp = fopen(filename, "wb");
    if (temp == NULL) {
        return 0;
    }
    fwrite(data, 1, size, temp);
    fclose(temp);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = gzeof(file);

    // Clean up
    gzclose(file);
    remove(filename);

    return 0;
}