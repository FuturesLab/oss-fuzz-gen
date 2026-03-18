#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_329(const uint8_t *data, size_t size) {
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

    // Set some basic TIFF fields
    TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    // Prepare data for TIFFWriteEncodedStrip
    uint32_t strip = 0;
    tmsize_t dataSize = static_cast<tmsize_t>(size);

    // Call the function-under-test
    TIFFWriteEncodedStrip(tiff, strip, (void *)data, dataSize);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}