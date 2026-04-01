#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include unistd.h for write and close functions

extern "C" {
    int TIFFIsMSB2LSB(TIFF *);
}

extern "C" int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    int result = TIFFIsMSB2LSB(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}