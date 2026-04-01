#define _LARGEFILE64_SOURCE  // Enable large file support

#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h> // Include this header for off64_t

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure the data size is non-zero to avoid creating an empty file
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    assert(tempFile != NULL);

    // Write the data to the temporary file
    size_t written = fwrite(data, 1, size, tempFile);
    assert(written == size);

    // Rewind the file pointer to the beginning
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    assert(gzfile != NULL);

    // Buffer to read data from the gzFile
    char buffer[1024];
    int bytesRead;

    // Read and process the data from the gzFile
    while ((bytesRead = gzread(gzfile, buffer, sizeof(buffer))) > 0) {
        // Process the data read from the gzFile
        // For demonstration purposes, we will just print the number of bytes read
        // In a real fuzz target, you would invoke the function under test here
        printf("Read %d bytes from gzFile\n", bytesRead);
    }

    // Check for errors in reading
    if (bytesRead < 0) {
        int err;
        const char *errorString = gzerror(gzfile, &err);
        fprintf(stderr, "Error reading gzFile: %s\n", errorString);
    }

    // Close the gzFile and the temporary file
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}