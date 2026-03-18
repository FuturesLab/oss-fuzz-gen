#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for 'close'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF image
    char tmpl[] = "/tmp/fuzz_tiff_XXXXXX";
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
    TIFF *tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Set some basic TIFF fields
    TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, 1); // width of the image
    TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, 1); // height of the image
    TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 1); // samples per pixel
    TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 8); // bits per sample
    TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT); // orientation
    TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG); // planar configuration
    TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK); // photometric interpretation

    // Ensure data size is sufficient for a scanline
    if (size < 1) {
        TIFFClose(tiff);
        fclose(file);
        return 0;
    }

    // Write the scanline
    uint32_t row = 0;
    uint16_t sample = 0;
    TIFFWriteScanline(tiff, (void *)data, row, sample);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}