#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For write, close, unlink

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Create temporary file for fuzzing
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Define mode for opening the TIFF file
    const char *mode = "r"; // Open for reading

    // Call the function-under-test
    TIFF *tiff = TIFFOpen(tmpl, mode);

    // Clean up
    if (tiff != NULL) {
        TIFFClose(tiff);
    }
    unlink(tmpl); // Delete the temporary file

    return 0;
}