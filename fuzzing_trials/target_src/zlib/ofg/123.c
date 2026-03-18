#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
    const char* temp_filename = "temp.gz";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    if (fwrite(data, 1, size, temp_file) != size) {
        fclose(temp_file);
        return 0;
    }
    fclose(temp_file);

    // Open the temporary file as a gzFile
    gzFile gz_file = gzopen(temp_filename, "rb");
    if (gz_file == NULL) {
        return 0;
    }

    // Read data from the gzFile to ensure the function under test is utilized
    char buffer[1024];
    while (gzread(gz_file, buffer, sizeof(buffer)) > 0) {
        // Process the buffer if necessary
    }

    // Call the function-under-test
    off_t position = gztell(gz_file);

    // Clean up
    gzclose(gz_file);
    remove(temp_filename);

    return 0;
}