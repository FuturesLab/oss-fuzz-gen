#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close and write

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    tdir_t dir = TIFFCurrentDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}