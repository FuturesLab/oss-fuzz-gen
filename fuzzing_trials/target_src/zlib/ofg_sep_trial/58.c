#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <unistd.h> // Include for off_t

// Function to initialize a gzFile for testing
gzFile initialize_gzfile() {
    // Create a temporary file
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return NULL;
    }

    // Write some data to the file
    fputs("This is a test data for gzFile.\n", tempFile);
    fflush(tempFile);

    // Rewind the file to the beginning
    rewind(tempFile);

    // Open the file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
    }

    return gzfile;
}

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize a gzFile
    gzFile gzfile = initialize_gzfile();
    if (gzfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    off_t offset = gztell(gzfile); // Use gztell which returns off_t

    // Print the offset for debugging purposes
    printf("Offset: %lld\n", (long long)offset);

    // Close the gzFile
    gzclose(gzfile);

    return 0;
}