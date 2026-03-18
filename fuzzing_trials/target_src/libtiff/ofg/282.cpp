#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close() and write()
#include <fcntl.h>   // Include for mkstemp()

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_282(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    void *buffer = nullptr;
    uint32_t x = 0, y = 0, z = 0;
    uint16_t sample = 0;
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

    close(fd);

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        return 0;
    }

    // Allocate a buffer for the tile data
    tmsize_t tileSize = TIFFTileSize(tiff);
    if (tileSize > 0) {
        buffer = malloc(tileSize);
        if (!buffer) {
            TIFFClose(tiff);
            return 0;
        }
        memset(buffer, 0, tileSize);
    }

    // Call the function-under-test
    TIFFWriteTile(tiff, buffer, x, y, z, sample);

    // Clean up
    if (buffer) {
        free(buffer);
    }
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}