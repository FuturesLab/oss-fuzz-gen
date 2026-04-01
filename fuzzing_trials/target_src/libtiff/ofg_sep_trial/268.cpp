#include <tiffio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // Include for close, write, and unlink

extern "C" int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        // Call the function-under-test
        int result = TIFFIsBigEndian(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}