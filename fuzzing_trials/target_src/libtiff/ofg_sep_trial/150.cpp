#include <tiffio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for 'write' and 'close' functions
#include <fcntl.h>   // Include for 'mkstemp' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        remove(tmpl);
        return 0;
    }

    // Initialize parameters for TIFFGetField
    uint32_t tag = 0; // Example tag value, can be adjusted
    void *value = malloc(1024); // Allocate memory for the value

    // Call the function-under-test
    TIFFGetField(tiff, tag, value);

    // Clean up
    free(value);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}