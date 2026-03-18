#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file with libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        unlink(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadTile
    void *buf = malloc(TIFFTileSize(tiff));
    if (!buf) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Call the function-under-test
    TIFFReadTile(tiff, buf, x, y, z, sample);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}