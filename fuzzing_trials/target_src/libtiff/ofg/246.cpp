#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h> // Include for mkstemp

extern "C" {
    // Include necessary C headers and functions
    int TIFFCreateGPSDirectory(TIFF *);
}

extern "C" int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Create a temporary file to initialize a TIFF structure
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the TIFF file
    TIFF *tiff = TIFFFdOpen(fd, tmpl, "r+");
    if (tiff == NULL) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    TIFFCreateGPSDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}