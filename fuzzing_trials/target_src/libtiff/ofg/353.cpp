#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_353(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t tile;
    void *buf;
    tmsize_t buflen;
    tmsize_t result;

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        return 0;
    }

    // Initialize parameters for TIFFReadEncodedTile
    tile = 0;  // Start with the first tile
    buflen = TIFFTileSize(tiff);
    buf = malloc(buflen);
    if (buf == NULL) {
        TIFFClose(tiff);
        return 0;
    }

    // Call the function-under-test
    result = TIFFReadEncodedTile(tiff, tile, buf, buflen);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}