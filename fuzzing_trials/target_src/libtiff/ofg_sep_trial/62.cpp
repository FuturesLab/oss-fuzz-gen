#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Allocate a buffer for the tile data
    tmsize_t tileSize = TIFFTileSize(tiff);
    void *tileBuffer = malloc(tileSize);
    if (tileBuffer == nullptr) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    // Define tile coordinates and sample
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Call the function-under-test
    TIFFReadTile(tiff, tileBuffer, x, y, z, sample);

    // Clean up
    free(tileBuffer);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}