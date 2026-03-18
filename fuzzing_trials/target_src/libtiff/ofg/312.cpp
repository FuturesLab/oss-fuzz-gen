#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include for write(), close(), and remove()

extern "C" {
    // Include necessary C headers and code here
}

extern "C" int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
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
    TIFFSizeProc sizeProc = TIFFGetSizeProc(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}