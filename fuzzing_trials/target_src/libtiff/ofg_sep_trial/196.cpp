#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>  // Include for 'write' and 'close'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    TIFF *tif = nullptr;
    void *scanline = nullptr;
    uint32_t row = 0;
    uint16_t sample = 0;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor so TIFFOpen can open it
    close(fd);

    // Open the temporary file as a TIFF image
    tif = TIFFOpen(tmpl, "r+");
    if (!tif) {
        return 0;
    }

    // Allocate memory for the scanline
    tsize_t scanlineSize = TIFFScanlineSize(tif);
    scanline = malloc(scanlineSize);
    if (!scanline) {
        TIFFClose(tif);
        return 0;
    }

    // Initialize the scanline with data
    memcpy(scanline, data, scanlineSize < size ? scanlineSize : size);

    // Fuzz the TIFFWriteScanline function
    TIFFWriteScanline(tif, scanline, row, sample);

    // Clean up
    free(scanline);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}