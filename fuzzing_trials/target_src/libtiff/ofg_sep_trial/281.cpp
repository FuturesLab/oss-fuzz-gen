#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Temporary file creation for TIFF
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

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (!tif) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFWriteTile
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;
    void *buffer = malloc(TIFFTileSize(tif));
    if (!buffer) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    tmsize_t result = TIFFWriteTile(tif, buffer, x, y, z, sample);

    // Clean up
    free(buffer);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}