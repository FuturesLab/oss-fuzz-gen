#include <tiffio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this header for 'close' and 'write' functions

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Create a temporary file to act as a TIFF file
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == NULL) {
        return 0;
    }

    // Use a non-zero directory index for fuzzing
    tdir_t dirIndex = 1;

    // Call the function under test
    TIFFUnlinkDirectory(tiff, dirIndex);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}