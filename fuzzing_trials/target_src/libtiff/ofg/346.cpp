#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for 'write', 'close', 'unlink'

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_346(const uint8_t *data, size_t size) {
    TIFF *tiff;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd < 0) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);  // Use 'unlink' instead of 'remove' for file removal
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r+");
    if (tiff == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFWriteRawTile
    uint32_t tile = 0; // Assuming the first tile for fuzzing
    void *buf = malloc(size);
    if (buf == NULL) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }
    memcpy(buf, data, size);
    tmsize_t bufsize = (tmsize_t)size;

    // Call the function-under-test
    TIFFWriteRawTile(tiff, tile, buf, bufsize);

    // Cleanup
    free(buf);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}