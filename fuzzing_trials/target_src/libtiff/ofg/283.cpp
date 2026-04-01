#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include unistd.h for the close() function

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    TIFF *tiff;
    void *buffer;
    uint32_t x = 0, y = 0, z = 0;
    uint16_t sample = 0;
    char tmpl[] = "/tmp/fuzz-tiffXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    close(fd);

    // Create a new TIFF file
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        return 0;
    }

    // Ensure the buffer is not NULL and has a size
    if (size > 0) {
        buffer = malloc(size);
        if (!buffer) {
            TIFFClose(tiff);
            return 0;
        }
        memcpy(buffer, data, size);
    } else {
        TIFFClose(tiff);
        return 0;
    }

    // Call the function-under-test
    TIFFWriteTile(tiff, buffer, x, y, z, sample);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}