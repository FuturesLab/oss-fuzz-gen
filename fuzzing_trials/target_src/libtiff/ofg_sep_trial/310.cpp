#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file with TIFFOpen
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFSizeProc sizeProc = TIFFGetSizeProc(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}