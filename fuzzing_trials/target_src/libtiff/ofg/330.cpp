#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include this header for the 'close' function

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_330(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t strip = 0;
    tmsize_t result;

    // Create a temporary file for TIFF
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Initialize TIFF structure
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        close(fd);
        return 0;
    }

    // Ensure the data is not NULL and has a reasonable size
    void *buffer = malloc(size);
    if (!buffer) {
        TIFFClose(tiff);
        close(fd);
        return 0;
    }
    memcpy(buffer, data, size);

    // Call the function-under-test
    result = TIFFWriteEncodedStrip(tiff, strip, buffer, (tmsize_t)size);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}