#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include this header for 'close' and 'remove'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF image
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadTile
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Allocate a buffer for the tile
    tmsize_t tileSize = TIFFTileSize(tiff);
    if (tileSize <= 0) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }
    void *buffer = _TIFFmalloc(tileSize);
    if (!buffer) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadTile(tiff, buffer, x, y, z, sample);

    // Clean up
    _TIFFfree(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}