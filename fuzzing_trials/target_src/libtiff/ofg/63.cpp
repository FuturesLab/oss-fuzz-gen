#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
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
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Set up parameters for TIFFReadTile
    void *buffer = malloc(TIFFTileSize(tiff));
    if (!buffer) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Call the function-under-test
    TIFFReadTile(tiff, buffer, x, y, z, sample);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}