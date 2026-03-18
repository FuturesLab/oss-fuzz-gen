#include <tiffio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
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

    // Open the file using TIFFFdOpen
    const char *mode = "r";
    TIFF *tiff = TIFFFdOpen(fd, tmpl, mode);
    if (tiff != NULL) {
        // Perform operations on the TIFF file if needed
        TIFFClose(tiff);
    }

    // Clean up
    close(fd);
    unlink(tmpl);

    return 0;
}