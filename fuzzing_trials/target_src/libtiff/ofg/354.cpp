#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>  // Include for write, close, and unlink

extern "C" int LLVMFuzzerTestOneInput_354(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t tile = 0;
    tmsize_t buffer_size = 1024;
    void *buffer = malloc(buffer_size);

    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(buffer);
        return 0;
    }

    // Write the input data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        // Call the function-under-test
        TIFFReadEncodedTile(tiff, tile, buffer, buffer_size);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up
    free(buffer);
    unlink(tmpl);  // Use unlink instead of remove for POSIX compliance

    return 0;
}