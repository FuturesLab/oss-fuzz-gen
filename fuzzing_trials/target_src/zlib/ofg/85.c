#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for gzputs
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Create a temporary file for gzopen
    const char *filename = "/tmp/fuzz_gzputs.gz";
    gzFile gz_file = gzopen(filename, "wb");
    if (gz_file == NULL) {
        free(input_data);
        return 0;
    }

    // Call the function under test
    gzputs(gz_file, input_data);

    // Clean up
    gzclose(gz_file);
    free(input_data);

    return 0;
}