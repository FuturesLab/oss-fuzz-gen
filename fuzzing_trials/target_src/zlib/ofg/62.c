#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    gzFile file;
    int errnum = 0;
    const char *error_msg;
    char buffer[1024]; // Buffer to read decompressed data

    // Create a temporary file for the gzFile
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Open the temporary file as a gzFile
    file = gzdopen(fileno(temp_file), "rb");
    if (file == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Attempt to read from the gzFile to invoke decompression logic
    while (gzread(file, buffer, sizeof(buffer)) > 0) {
        // Reading the data, but not doing anything with it
    }

    // Check for errors after reading
    error_msg = gzerror(file, &errnum);
    if (errnum != Z_OK && errnum != Z_STREAM_END) {
        fprintf(stderr, "gzerror: %s\n", error_msg);
    }

    // Clean up
    gzclose(file);
    fclose(temp_file);

    return 0;
}