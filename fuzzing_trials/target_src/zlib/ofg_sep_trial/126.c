#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
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
        remove(filename);
        return 0;
    }

    // Buffer to read data from the gzFile
    char buffer[1024];
    int bytesRead;

    // Read from gzfile to ensure the function under test is invoked
    while ((bytesRead = gzread(gzfile, buffer, sizeof(buffer))) > 0) {
        // Do something with the read data if needed
    }

    // Check for errors
    if (gzeof(gzfile)) {
        // End of file reached, no error
    } else {
        // An error occurred, clear it
        gzclearerr(gzfile);
    }

    // Clean up
    gzclose(gzfile);
    remove(filename);

    return 0;
}