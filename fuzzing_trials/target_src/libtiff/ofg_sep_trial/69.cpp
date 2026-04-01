#include <tiffio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for 'close' and 'write' functions

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Create a temporary file to store the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) { // Cast size to ssize_t for comparison
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == NULL) {
        remove(tmpl);
        return 0;
    }

    // Prepare the buffer for reading raw tile data
    tmsize_t buffer_size = 1024; // Arbitrary buffer size
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint32_t tile = 0; // Start with the first tile
    tmsize_t result = TIFFReadRawTile(tif, tile, buffer, buffer_size);

    // Clean up
    free(buffer);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}