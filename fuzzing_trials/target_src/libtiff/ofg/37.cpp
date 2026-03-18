#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // Include for write, close, and mkstemp
#include <stdlib.h> // Include for remove

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file using the TIFF library
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        // Call the function-under-test
        TIFFCleanup(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}