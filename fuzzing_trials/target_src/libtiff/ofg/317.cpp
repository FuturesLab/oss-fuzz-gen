#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_317(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare a buffer to read a scanline
    tsize_t scanlineSize = TIFFScanlineSize(tiff);
    if (scanlineSize <= 0) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }
    void *buf = _TIFFmalloc(scanlineSize);
    if (buf == nullptr) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Fuzzing parameters for the TIFFReadScanline function
    uint32_t row = 0; // Typically the starting row
    uint16_t sample = 0; // Typically the starting sample

    // Call the function-under-test
    TIFFReadScanline(tiff, buf, row, sample);

    // Clean up
    _TIFFfree(buf);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}