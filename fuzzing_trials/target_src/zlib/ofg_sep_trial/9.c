#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove the 'extern "C"' linkage specification for C++ as this is a C file
int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "tempfile.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        remove(filename);
        return 0;
    }
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        remove(filename);
        return 0;
    }

    // Attempt to read from the gzFile to ensure coverage
    char buffer[4096];
    while (gzread(gzfile, buffer, sizeof(buffer)) > 0) {
        // Process the buffer if needed
    }

    // Call the function-under-test
    gzrewind(gzfile);

    // Close the gzFile
    gzclose(gzfile);

    // Remove the temporary file
    remove(filename);

    return 0;
}