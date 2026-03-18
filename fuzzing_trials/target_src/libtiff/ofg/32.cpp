#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>  // Include for close and unlink

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to contain at least one tile of data
    if (size < 1024) {
        return 0;
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzz_tiffXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen(tmpl, "w+");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Set up TIFF fields (example values)
    TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, 256);
    TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, 256);
    TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 3);
    TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(tiff, TIFFTAG_TILEWIDTH, 128);
    TIFFSetField(tiff, TIFFTAG_TILELENGTH, 128);

    // Calculate tile size
    tmsize_t tileSize = TIFFTileSize(tiff);

    // Ensure data size is sufficient for at least one tile
    if (size < static_cast<size_t>(tileSize)) {
        TIFFClose(tiff);
        fclose(file);
        return 0;
    }

    // Write encoded tile
    uint32_t tileIndex = 0;
    tmsize_t result = TIFFWriteEncodedTile(tiff, tileIndex, (void *)data, tileSize);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    unlink(tmpl);

    return 0;
}