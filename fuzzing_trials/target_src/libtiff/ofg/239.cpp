#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>  // For close, write, and mkstemp
#include <fcntl.h>   // For open
#include <sys/types.h> // For ssize_t
#include <stdlib.h>  // For mkstemp

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    TIFF *tif = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0; // Failed to create temp file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0; // Failed to write data to file
    }

    // Close the file descriptor
    close(fd);

    // Open the file with libtiff
    tif = TIFFOpen(tmpl, "r+");
    if (tif != nullptr) {
        // Call the function under test
        TIFFFlush(tif);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}