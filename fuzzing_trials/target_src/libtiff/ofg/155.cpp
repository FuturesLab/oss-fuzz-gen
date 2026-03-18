#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tiffio.h>
#include <unistd.h> // Include for close and write functions

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create temp file
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0; // Failed to write data
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        remove(tmpl);
        return 0; // Failed to open TIFF file
    }

    // Prepare parameters for TIFFGetField
    uint32_t tag = *(uint32_t *)data; // Use the first 4 bytes as the tag
    void *value = malloc(1024); // Allocate memory for the value

    // Call the function-under-test
    TIFFGetField(tiff, tag, value);

    // Clean up
    free(value);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}