#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this for close() and unlink()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_345(const uint8_t *data, size_t size) {
    TIFF *tif = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Initialize TIFF
    tif = TIFFOpen(tmpl, "w");
    if (!tif) {
        close(fd);
        return 0;
    }

    // Ensure the file has a basic TIFF structure
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    // Call TIFFWriteRawTile with fuzz data
    uint32_t tileIndex = 0; // Use tile index 0 for simplicity
    void *buffer = malloc(size);
    if (buffer) {
        memcpy(buffer, data, size);
        tmsize_t result = TIFFWriteRawTile(tif, tileIndex, buffer, static_cast<tmsize_t>(size));
        (void)result; // Use result if needed for debugging
        free(buffer);
    }

    // Clean up
    TIFFClose(tif);
    close(fd);
    unlink(tmpl);

    return 0;
}