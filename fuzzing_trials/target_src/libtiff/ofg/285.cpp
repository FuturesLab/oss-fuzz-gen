#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this header for the close() function

extern "C" {
    // All headers, functions, and code from the libtiff project must be wrapped in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_285(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t strip = 0;
    void *buffer;
    tmsize_t bufferSize;

    // Create a temporary file to work with TIFF
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Initialize a TIFF structure
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Allocate a buffer and copy the data into it
    bufferSize = (tmsize_t)size;
    buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tiff);
        fclose(file);
        return 0;
    }
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFWriteRawStrip(tiff, strip, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}