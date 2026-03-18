#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // For close()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_353(const uint8_t *data, size_t size) {
    // Remove the check for sizeof(TIFF) as it's an incomplete type
    // and we cannot determine its size. Instead, ensure there's enough
    // data to attempt processing.
    if (size == 0) {
        return 0; // No data to process
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open the file descriptor as a file
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Prepare buffer for reading tile
    tmsize_t tileSize = TIFFTileSize(tiff);
    if (tileSize <= 0) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0; // Invalid tile size
    }

    void *buffer = _TIFFmalloc(tileSize);
    if (!buffer) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0; // Failed to allocate buffer
    }

    // Attempt to read the first tile (tile index 0)
    TIFFReadEncodedTile(tiff, 0, buffer, tileSize);

    // Clean up
    _TIFFfree(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}